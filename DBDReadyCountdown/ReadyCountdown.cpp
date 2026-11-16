#include "ReadyCountdown.h"

#include <cmath>






bool ReadyCountdown::IsCustomGame(SDK::UWorld* world)
{
	SDK::UGameInstance* gameInstance = world->OwningGameInstance;
	if (gameInstance == nullptr)
		return false;

	uintptr_t persistentDataAddress = Utilities::Memory::Internal::AddressDereference(reinterpret_cast<uintptr_t>(gameInstance), persistentDataOffset);
	if (persistentDataAddress == 0x0)
		return false;

	uintptr_t gameTypeAddress = Utilities::Memory::Internal::AddressAddOffset(persistentDataAddress, gameTypeOffset);
	if (gameTypeAddress == 0x0)
		return false;

	return *reinterpret_cast<uint8_t*>(gameTypeAddress) == static_cast<uint8_t>(SDK::EGameType::KillYourFriends);
}

void ReadyCountdown::Process()
{
	SDK::UWorld* world = SDK::UWorld::GetWorld();
	if (world == nullptr || Utilities::Game::IsInOnlineLobby(world) == false)
	{
		hasTriggered = false;
		isPaused = false;
		return;
	}

	/* Only the host owns the lobby game mode; clients get the new timer through replication. */
	SDK::AGameModeBase* gameMode = world->AuthorityGameMode;
	if (gameMode == nullptr || gameMode->IsA(SDK::ADBDGame_Lobby::StaticClass()) == false)
	{
		isPaused = false;
		return;
	}

	SDK::AGameStateBase* gameState = world->GameState;
	if (gameState == nullptr)
		return;

	uintptr_t countdownAddress = Utilities::Memory::Internal::AddressAddOffset(reinterpret_cast<uintptr_t>(gameMode), lobbyTimerOffset);
	if (countdownAddress == 0x0)
		return;

	/* The host is the local player on the listen server. */
	SDK::ADBDPlayerState* hostPlayerState = nullptr;
	SDK::APlayerController* hostController = SDK::UGameplayStatics::GetPlayerController(world, 0);
	if (hostController != nullptr && hostController->PlayerState != nullptr && hostController->PlayerState->IsA(SDK::ADBDPlayerState::StaticClass()))
		hostPlayerState = static_cast<SDK::ADBDPlayerState*>(hostController->PlayerState);

	int32_t playerCount = 0;
	bool allPlayersReady = true;

	for (int32_t i = 0; i < gameState->PlayerArray.Num(); i++)
	{
		SDK::APlayerState* playerState = gameState->PlayerArray[i];
		if (playerState == nullptr || playerState->IsA(SDK::ADBDPlayerState::StaticClass()) == false)
			continue;

		SDK::ADBDPlayerState* dbdPlayerState = static_cast<SDK::ADBDPlayerState*>(playerState);
		if (dbdPlayerState->GameRole == SDK::EPlayerRole::VE_Observer)
			continue;

		playerCount++;

		/* Bots never press ready, so they don't hold the countdown back. */
		if (dbdPlayerState->bIsABot == false && dbdPlayerState->IsPlayerReady == false)
			allPlayersReady = false;
	}

	float countdownValue = Utilities::Memory::Internal::GetFloat(countdownAddress);
	bool isCustomGame = IsCustomGame(world);


	/* Custom games only: hold the lobby timer while the host isn't ready (spectating hosts don't hold it). */
	bool shouldPause = hostPlayerState != nullptr
		&& hostPlayerState->GameRole != SDK::EPlayerRole::VE_Observer
		&& hostPlayerState->IsPlayerReady == false
		&& isCustomGame;

	if (shouldPause)
	{
		if (isPaused == false)
		{
			/* Timer <= 0 means no countdown is running, nothing to hold.
			   Never hold the final 5.9s countdown either: the game doesn't let anyone unready during it. */
			if (countdownValue <= 0.0f || countdownValue <= countdownValue_AllReady)
				return;

			/* Hold at X.5 so the displayed whole seconds don't flicker between our writes. */
			pausedValue = countdownValue >= 1.0f ? std::floor(countdownValue) + 0.5f : countdownValue;
			isPaused = true;
			Utilities::Game::Print(L"[DBDReadyCountdown] Host isn't ready, timer paused at %.2f\n", pausedValue);
		}

		Utilities::Memory::Internal::SetFloat(countdownAddress, pausedValue);
		return;
	}

	if (isPaused)
	{
		isPaused = false;
		Utilities::Game::Print(L"[DBDReadyCountdown] Host is ready, timer resumed from %.2f\n", pausedValue);
	}


	/* Public lobbies need a full lobby, custom games just need everyone present (host alone is fine). */
	int32_t requiredPlayers = isCustomGame ? requiredPlayerCount_CustomGame : requiredPlayerCount_Public;
	if (playerCount < requiredPlayers || allPlayersReady == false)
	{
		hasTriggered = false;
		return;
	}

	if (hasTriggered)
		return;

	static const float countdownRange_Min = -1.0f;
	static const float countdownRange_Max = 131072.0f;

	if (countdownValue < countdownRange_Min || countdownValue > countdownRange_Max)
	{
		Utilities::Game::Print(L"[DBDReadyCountdown] Countdown value is out of range (%.2f)\n", countdownValue);
		hasTriggered = true;
		return;
	}

	hasTriggered = true;

	/* Already counting down from 5.9 or less (native logic or DBD_ForceStartMatch got there first). */
	if (countdownValue > countdownRange_Min && countdownValue <= countdownValue_AllReady)
		return;

	if (Utilities::Memory::Internal::SetFloat(countdownAddress, countdownValue_AllReady) == false)
	{
		Utilities::Game::Print(L"[DBDReadyCountdown] Failed to change countdown value\n");
		return;
	}

	Utilities::Game::Print(L"[DBDReadyCountdown] All %d players ready, _timerValue = %.2f (was %.2f)\n", playerCount, countdownValue_AllReady, countdownValue);
}

DWORD WINAPI ReadyCountdown::ThreadSafeWorker()
{
	printf("[DBDReadyCountdown] ThreadSafeWorker() is now entering the loop\n");

	while (true)
	{
		EXCEPTION_POINTERS* exceptionInfo = nullptr;

		__try
		{
			Process();

			/* While holding the timer, rewrite it often so the countdown barely moves between writes. */
			Sleep(isPaused ? 10 : 100);
		}
		__except (exceptionInfo = GetExceptionInformation(), EXCEPTION_EXECUTE_HANDLER)
		{
			if (exceptionInfo)
			{
				void* crashAddress = exceptionInfo->ExceptionRecord->ExceptionAddress;
				DWORD exceptionCode = exceptionInfo->ExceptionRecord->ExceptionCode;

				HMODULE hModule = GetModuleHandle(nullptr);
				uintptr_t baseAddress = (uintptr_t)hModule;
				uintptr_t relativeOffset = (uintptr_t)crashAddress - baseAddress;

				printf("[DBDReadyCountdown] FATAL ERROR / CRASH in %s\n", __FUNCSIG__);
				printf("[DBDReadyCountdown] Exception Code:   0x%08X\n", exceptionCode);
				printf("[DBDReadyCountdown] Absolute Address: 0x%llX\n", (unsigned long long)crashAddress);
				printf("[DBDReadyCountdown] Module Base:      0x%llX\n", (unsigned long long)baseAddress);
				printf("[DBDReadyCountdown] Relative Offset:  0x%llX\n", (unsigned long long)relativeOffset);
			}

			printf("[DBDReadyCountdown] Restarting loop in 3 seconds...\n");
			Sleep(3000);
		}
	}

	return 0;
}




void ReadyCountdown::Init()
{
	printf("[DBDReadyCountdown] Starting initialization sequence...\n");
	while (Utilities::Game::IsInitialized() == false)
	{
		Sleep(10);
	}

	printf("[DBDReadyCountdown] Game is initialized, starting ThreadSafeWorker()...\n");
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadSafeWorker, 0, 0, 0);
}
