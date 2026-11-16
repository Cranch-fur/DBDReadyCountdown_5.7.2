#pragma once
#include "Utilities.h"






class ReadyCountdown
{
private:
	/* Lobby must have this many players (killer + survivors, spectators excluded) before the countdown is shortened. */
	static inline const int32_t requiredPlayerCount = 5;

	/* Same value DBD_ForceStartMatch and the native ADBDGame_Lobby::SetTimer() use. */
	static inline const float countdownValue_AllReady = 5.9000001f;

	/* ADBDGame_Lobby::_timerValue (5.7.2, not exposed by the SDK, inside Pad_378). */
	static inline const uintptr_t lobbyTimerOffset = 0x3B4;

	static inline bool hasTriggered = false;


	static void Process();
	static DWORD WINAPI ThreadSafeWorker();


public:
	static void Init();
};
