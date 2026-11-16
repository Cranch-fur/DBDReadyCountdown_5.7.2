#pragma once
#include "Utilities.h"






class ReadyCountdown
{
private:
	/* Players (killer + survivors, spectators excluded) needed before the countdown is shortened. */
	static inline const int32_t requiredPlayerCount_Public = 5;
	static inline const int32_t requiredPlayerCount_CustomGame = 1;

	/* Same value DBD_ForceStartMatch and the native ADBDGame_Lobby::SetTimer() use. */
	static inline const float countdownValue_AllReady = 5.9000001f;

	/* ADBDGame_Lobby::_timerValue (5.7.2, not exposed by the SDK, inside Pad_378). */
	static inline const uintptr_t lobbyTimerOffset = 0x3B4;

	/* UDBDGameInstance::_persistentData, then game type byte inside it (EGameType::KillYourFriends = custom game). */
	static inline const uintptr_t persistentDataOffset = 0x720;
	static inline const uintptr_t gameTypeOffset = 0xC0;

	static inline bool hasTriggered = false;

	static inline bool isPaused = false;
	static inline float pausedValue = 0.0f;


	static bool IsCustomGame(SDK::UWorld* world);


	static void Process();
	static DWORD WINAPI ThreadSafeWorker();


public:
	static void Init();
};
