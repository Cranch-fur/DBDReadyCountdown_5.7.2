#include "ReadyCountdown.h"






void ReadyCountdown::Process()
{
	SDK::UWorld* world = SDK::UWorld::GetWorld();
	if (world == nullptr || Utilities::Game::IsInOnlineLobby(world) == false)
	{
		hasTriggered = false;
		return;
	}

	/* Only the host owns the lobby game mode; clients get the new timer through replication. */
	SDK::AGameModeBase* gameMode = world->AuthorityGameMode;
	if (gameMode == nullptr || gameMode->IsA(SDK::ADBDGame_Lobby::StaticClass()) == false)
		return;

	SDK::AGameStateBase* gameState = world->GameState;
	if (gameState == nullptr)
		return;

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

	if (playerCount < requiredPlayerCount || allPlayersReady == false)
	{
		hasTriggered = false;
		return;
	}

	if (hasTriggered)
		return;

	uintptr_t countdownAddress = Utilities::Memory::Internal::AddressAddOffset(reinterpret_cast<uintptr_t>(gameMode), lobbyTimerOffset);
	if (countdownAddress == 0x0)
	{
		Utilities::Game::Print(L"[DBDReadyCountdown] Failed to find countdown\n");
		return;
	}

	static const float countdownRange_Min = -1.0f;
	static const float countdownRange_Max = 131072.0f;

	float countdownValue = Utilities::Memory::Internal::GetFloat(countdownAddress);
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
			Sleep(100);
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
