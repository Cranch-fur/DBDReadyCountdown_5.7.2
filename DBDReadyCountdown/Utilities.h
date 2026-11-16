#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cwctype>
#include <cstdlib>
#include <cstdint>
#include <utility>

#include "Windows.h"
#include "SDK.hpp"

#pragma comment(lib, "shell32.lib")






namespace Utilities
{
	class CommandLine
	{
	public:
		static std::string Get();
		static std::wstring GetUtf16();

		static std::vector<std::string> GetArguments();
		static std::vector<std::wstring> GetArgumentsUtf16();

		static int Count();

		static bool HasArgument(const std::string& argument);
		static bool HasArgument(const std::wstring& argument);
		static bool HasArgument(const char* argument);
		static bool HasArgument(const wchar_t* argument);
	};




	class String
	{
	public:
		static std::string ToString(const std::wstring& wideString);
		static std::string ToString(const char* cString);
		static std::string ToString(const wchar_t* wcString);

		static std::wstring ToWString(const std::string& string);
		static std::wstring ToWString(const char* cString);
		static std::wstring ToWString(const wchar_t* wcString);


		static std::string ToLowerCase(std::string string);
		static std::wstring ToLowerCase(std::wstring wString);
		static std::string ToLowerCase(const char* cString);
		static std::wstring ToLowerCase(const wchar_t* wcString);

		static std::string ToUpperCase(std::string string);
		static std::wstring ToUpperCase(std::wstring wString);
		static std::string ToUpperCase(const char* cString);
		static std::wstring ToUpperCase(const wchar_t* wcString);


		static std::string Replace(std::string string, const std::string& from, const std::string& to);
		static std::string Replace(const std::string& string, const std::string& from, const std::wstring& to);
		static std::string Replace(const std::string& string, const std::wstring& from, const std::string& to);
		static std::string Replace(const std::string& string, const std::wstring& from, const std::wstring& to);
		static std::string Replace(const char* cString, const char* from, const char* to);

		static std::wstring Replace(std::wstring wString, const std::wstring& from, const std::wstring& to);
		static std::wstring Replace(const std::wstring& wString, const std::wstring& from, const std::string& to);
		static std::wstring Replace(const std::wstring& wString, const std::string& from, const std::wstring& to);
		static std::wstring Replace(const std::wstring& wString, const std::string& from, const std::string& to);
		static std::wstring Replace(const wchar_t* wcString, const wchar_t* from, const wchar_t* to);


		static std::string ReplaceFirstOf(std::string string, const std::string& from, const std::string& to);
		static std::string ReplaceFirstOf(const std::string& string, const std::string& from, const std::wstring& to);
		static std::string ReplaceFirstOf(const std::string& string, const std::wstring& from, const std::string& to);
		static std::string ReplaceFirstOf(const std::string& string, const std::wstring& from, const std::wstring& to);
		static std::string ReplaceFirstOf(const char* cString, const char* from, const char* to);

		static std::wstring ReplaceFirstOf(std::wstring wString, const std::wstring& from, const std::wstring& to);
		static std::wstring ReplaceFirstOf(const std::wstring& wString, const std::wstring& from, const std::string& to);
		static std::wstring ReplaceFirstOf(const std::wstring& wString, const std::string& from, const std::wstring& to);
		static std::wstring ReplaceFirstOf(const std::wstring& wString, const std::string& from, const std::string& to);
		static std::wstring ReplaceFirstOf(const wchar_t* wcString, const wchar_t* from, const wchar_t* to);


		static std::string ReplaceLastOf(std::string string, const std::string& from, const std::string& to);
		static std::string ReplaceLastOf(const std::string& string, const std::string& from, const std::wstring& to);
		static std::string ReplaceLastOf(const std::string& string, const std::wstring& from, const std::string& to);
		static std::string ReplaceLastOf(const std::string& string, const std::wstring& from, const std::wstring& to);
		static std::string ReplaceLastOf(const char* cString, const char* from, const char* to);

		static std::wstring ReplaceLastOf(std::wstring wString, const std::wstring& from, const std::wstring& to);
		static std::wstring ReplaceLastOf(const std::wstring& wString, const std::wstring& from, const std::string& to);
		static std::wstring ReplaceLastOf(const std::wstring& wString, const std::string& from, const std::wstring& to);
		static std::wstring ReplaceLastOf(const std::wstring& wString, const std::string& from, const std::string& to);
		static std::wstring ReplaceLastOf(const wchar_t* wcString, const wchar_t* from, const wchar_t* to);


		static bool Contains(const std::string& string, const std::string& substring, const bool& useCase = true);
		static bool Contains(const std::string& string, const std::wstring& substring, const bool& useCase = true);
		static bool Contains(const char* cString, const char* substring, const bool& useCase = true);

		static bool Contains(const std::wstring& wString, const std::wstring& substring, const bool& useCase = true);
		static bool Contains(const std::wstring& wString, const std::string& substring, const bool& useCase = true);
		static bool Contains(const wchar_t* wcString, const wchar_t* substring, const bool& useCase = true);


		static bool StartsWith(const std::string& string, const std::string& substring, const bool& useCase = true);
		static bool StartsWith(const std::string& string, const std::wstring& substring, const bool& useCase = true);
		static bool StartsWith(const char* cString, const char* substring, const bool& useCase = true);

		static bool StartsWith(const std::wstring& wString, const std::wstring& substring, const bool& useCase = true);
		static bool StartsWith(const std::wstring& wString, const std::string& substring, const bool& useCase = true);
		static bool StartsWith(const wchar_t* wcString, const wchar_t* substring, const bool& useCase = true);


		static bool EndsWith(const std::string& string, const std::string& substring, const bool& useCase = true);
		static bool EndsWith(const std::string& string, const std::wstring& substring, const bool& useCase = true);
		static bool EndsWith(const char* cString, const char* substring, const bool& useCase = true);

		static bool EndsWith(const std::wstring& wString, const std::wstring& substring, const bool& useCase = true);
		static bool EndsWith(const std::wstring& wString, const std::string& substring, const bool& useCase = true);
		static bool EndsWith(const wchar_t* wcString, const wchar_t* substring, const bool& useCase = true);


		static std::vector<std::string> Split(const std::string& string, const char& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const std::wstring& wString, const char& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const char* cString, const char& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::string> Split(const wchar_t* wcString, const char& separator, const bool& removeSeparatorSpaces = true);

		static std::vector<std::wstring> Split(const std::string& string, const wchar_t& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const std::wstring& wideString, const wchar_t& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const char* cString, const wchar_t& separator, const bool& removeSeparatorSpaces = true);
		static std::vector<std::wstring> Split(const wchar_t* wcString, const wchar_t& separator, const bool& removeSeparatorSpaces = true);


		static std::string Reverse(std::string string);
		static std::wstring Reverse(std::wstring wString);
		static std::string Reverse(const char* cString);
		static std::wstring Reverse(const wchar_t* wcString);
	};




	class Game
	{
	public:
		enum class E_GameState
		{
			None,
			StartScreen,
			OfflineLobby,
			OnlineLobby,
			Tutorial,
			Match
		};


		static E_GameState GetGameState();
		static E_GameState GetGameState(SDK::UWorld* worldReference);

		static bool IsAtStartScreen();
		static bool IsAtStartScreen(SDK::UWorld* worldReference);

		static bool IsInOfflineLobby();
		static bool IsInOfflineLobby(SDK::UWorld* worldReference);

		static bool IsInOnlineLobby();
		static bool IsInOnlineLobby(SDK::UWorld* worldReference);

		static bool IsInTutorial();
		static bool IsInTutorial(SDK::UWorld* worldReference);

		static bool IsInMatch();
		static bool IsInMatch(SDK::UWorld* worldReference);


		static bool IsInMenuOrLobby();
		static bool IsInMenuOrLobby(SDK::UWorld* worldReference);

		static bool IsInGameplay();
		static bool IsInGameplay(SDK::UWorld* worldReference);


		static bool IsInitialized();


		static std::vector<SDK::APallet*> GetPallets();


		static void Print(const wchar_t* format, ...);
	};




	namespace Memory
	{
		class Internal // Functions within the class allows to manipulate memory of process program is running in.
		{
		public:
			/**
			* @brief Determines whether a given pointer refers to a valid, committed, and readable (or executable) memory region.
			* @param memoryPtr - Pointer to the memory location to check.
			* @return true if the region is committed, and has read or execute+read permissions; false otherwise.
			*/
			static bool IsValidPtr(const void* memoryPtr);
			/**
			* @brief Determines whether a given memory address refers to a valid, committed, and readable (or executable) memory region.
			* @param memoryAddress - Address of the memory location to check.
			* @return true if the region is committed, and has read or execute+read permissions; false otherwise.
			*/
			static bool IsValidAddress(const uintptr_t& memoryAddress);

			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param memoryPtr - Pointer to the starting memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid pointer to the memory location if both the beginning and end of the target region are readable;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrAddOffset(const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param memoryAddress - Address of the memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid pointer to the memory location if both the beginning and end of the target region are readable;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrAddOffset(const uintptr_t& memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param memoryPtr - Pointer to the starting memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid memory address if both the beginning and end of the target region are readable;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressAddOffset(const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address and verifies that the resulting address range is readable.
			* @param memoryAddress - Address of the memory location to which the offset will be added.
			* @param offset - The number of bytes to add to the base address.
			* @return The new valid memory address if both the beginning and end of the target region are readable;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressAddOffset(const uintptr_t& memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer.
			* @param memoryPtr - Pointer to the starting memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid pointer read from the memory location;
			*         otherwise returns 'nullptr' to indicate an invalid/unreadable address.
			*/
			static void* PtrDereference(const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer.
			* @param memoryAddress - Address of the memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid pointer read from the memory location;
			*         otherwise returns 'nullptr' to indicate an invalid/unreadable address.
			*/
			static void* PtrDereference(const uintptr_t& memoryAddress, size_t offset);

			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer.
			* @param memoryPtr - Pointer to the starting memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid memory address read from the memory location;
			*         otherwise returns '0x0' to indicate an invalid/unreadable address.
			*/
			static uintptr_t AddressDereference(const void* memoryPtr, size_t offset);
			/**
			* @brief Adds a byte offset to a base memory address, verifies readability, and dereferences it to read the next pointer.
			* @param memoryAddress - Address of the memory location.
			* @param offset - The number of bytes to add to the base address before dereferencing (default is 0).
			* @return The new valid memory address read from the memory location;
			*         otherwise returns '0x0' to indicate an invalid/unreadable address.
			*/
			static uintptr_t AddressDereference(const uintptr_t& memoryAddress, size_t offset);

			/**
			* @brief Follows a chain of pointers starting from a base address, applying a sequence of offsets.
			* @param memoryPtr - Pointer to the starting memory location from which the pointer chain will be resolved.
			* @return The new valid memory address if pointer chain was successfully resolved and final destination was reached;
			*         otherwise returns 'nullptr' to indicate an invalid or unreadable address.
			*/
			static void* PtrFollowPointerChain(const void* memoryPtr, const std::vector<uintptr_t>& memoryOffsets);
			/**
			* @brief Follows a chain of pointers starting from a base address, applying a sequence of offsets.
			* @param memoryAddress - Address of the memory location from which the pointer chain will be resolved.
			* @return The new valid memory address if pointer chain was successfully resolved and final destination was reached;
			*         otherwise returns '0x0' to indicate an invalid or unreadable address.
			*/
			static uintptr_t AddressFollowPointerChain(const uintptr_t& memoryAddress, const std::vector<uintptr_t>& memoryOffsets);




			/* For when 'memoryAddress' contains the actual value. */
			static bool GetBool(const void* memoryPtr);
			static bool GetBool(const uintptr_t& memoryAddress);

			static bool SetBool(const void* memoryPtr, bool newValue);
			static bool SetBool(const uintptr_t& memoryAddress, bool newValue);

			static bool PatchBool(const void* memoryPtr, bool from, bool to);
			static bool PatchBool(const uintptr_t& memoryAddress, bool from, bool to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static bool IndirectGetBool(const void* memoryPtr);
			static bool IndirectGetBool(const uintptr_t& memoryAddress);

			static bool IndirectSetBool(const void* memoryPtr, bool newValue);
			static bool IndirectSetBool(const uintptr_t& memoryAddress, bool newValue);

			static bool IndirectPatchBool(const void* memoryPtr, bool from, bool to);
			static bool IndirectPatchBool(const uintptr_t& memoryAddress, bool from, bool to);




			/* For when 'memoryAddress' contains the actual value. */
			static int8_t GetInt8(const void* memoryPtr);
			static int8_t GetInt8(const uintptr_t& memoryAddress);

			static bool   SetInt8(const void* memoryPtr, int8_t newValue);
			static bool   SetInt8(const uintptr_t& memoryAddress, int8_t newValue);

			static bool   PatchInt8(const void* memoryPtr, int8_t from, int8_t to);
			static bool   PatchInt8(const uintptr_t& memoryAddress, int8_t from, int8_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int8_t IndirectGetInt8(const void* memoryPtr);
			static int8_t IndirectGetInt8(const uintptr_t& memoryAddress);

			static bool   IndirectSetInt8(const void* memoryPtr, int8_t newValue);
			static bool   IndirectSetInt8(const uintptr_t& memoryAddress, int8_t newValue);

			static bool   IndirectPatchInt8(const void* memoryPtr, int8_t from, int8_t to);
			static bool   IndirectPatchInt8(const uintptr_t& memoryAddress, int8_t from, int8_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int16_t GetInt16(const void* memoryPtr);
			static int16_t GetInt16(const uintptr_t& memoryAddress);

			static bool    SetInt16(const void* memoryPtr, int16_t newValue);
			static bool    SetInt16(const uintptr_t& memoryAddress, int16_t newValue);

			static bool    PatchInt16(const void* memoryPtr, int16_t from, int16_t to);
			static bool    PatchInt16(const uintptr_t& memoryAddress, int16_t from, int16_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int16_t IndirectGetInt16(const void* memoryPtr);
			static int16_t IndirectGetInt16(const uintptr_t& memoryAddress);

			static bool    IndirectSetInt16(const void* memoryPtr, int16_t newValue);
			static bool    IndirectSetInt16(const uintptr_t& memoryAddress, int16_t newValue);

			static bool    IndirectPatchInt16(const void* memoryPtr, int16_t from, int16_t to);
			static bool    IndirectPatchInt16(const uintptr_t& memoryAddress, int16_t from, int16_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int32_t GetInt32(const void* memoryPtr);
			static int32_t GetInt32(const uintptr_t& memoryAddress);

			static bool    SetInt32(const void* memoryPtr, int32_t newValue);
			static bool    SetInt32(const uintptr_t& memoryAddress, int32_t newValue);

			static bool    PatchInt32(const void* memoryPtr, int32_t from, int32_t to);
			static bool    PatchInt32(const uintptr_t& memoryAddress, int32_t from, int32_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int32_t IndirectGetInt32(const void* memoryPtr);
			static int32_t IndirectGetInt32(const uintptr_t& memoryAddress);

			static bool	   IndirectSetInt32(const void* memoryPtr, int32_t newValue);
			static bool	   IndirectSetInt32(const uintptr_t& memoryAddress, int32_t newValue);

			static bool    IndirectPatchInt32(const void* memoryPtr, int32_t from, int32_t to);
			static bool    IndirectPatchInt32(const uintptr_t& memoryAddress, int32_t from, int32_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static int64_t GetInt64(const void* memoryPtr);
			static int64_t GetInt64(const uintptr_t& memoryAddress);

			static bool    SetInt64(const void* memoryPtr, int64_t newValue);
			static bool    SetInt64(const uintptr_t& memoryAddress, int64_t newValue);

			static bool    PatchInt64(const void* memoryPtr, int64_t from, int64_t to);
			static bool    PatchInt64(const uintptr_t& memoryAddress, int64_t from, int64_t to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static int64_t IndirectGetInt64(const void* memoryPtr);
			static int64_t IndirectGetInt64(const uintptr_t& memoryAddress);

			static bool    IndirectSetInt64(const void* memoryPtr, int64_t newValue);
			static bool    IndirectSetInt64(const uintptr_t& memoryAddress, int64_t newValue);

			static bool    IndirectPatchInt64(const void* memoryPtr, int64_t from, int64_t to);
			static bool    IndirectPatchInt64(const uintptr_t& memoryAddress, int64_t from, int64_t to);




			/* For when 'memoryAddress' contains the actual value. */
			static float GetFloat(const void* memoryPtr);
			static float GetFloat(const uintptr_t& memoryAddress);

			static bool  SetFloat(const void* memoryPtr, float newValue);
			static bool  SetFloat(const uintptr_t& memoryAddress, float newValue);

			static bool  PatchFloat(const void* memoryPtr, float from, float to);
			static bool  PatchFloat(const uintptr_t& memoryAddress, float from, float to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static float IndirectGetFloat(const void* memoryPtr);
			static float IndirectGetFloat(const uintptr_t& memoryAddress);

			static bool  IndirectSetFloat(const void* memoryPtr, float newValue);
			static bool  IndirectSetFloat(const uintptr_t& memoryAddress, float newValue);

			static bool  IndirectPatchFloat(const void* memoryPtr, float from, float to);
			static bool  IndirectPatchFloat(const uintptr_t& memoryAddress, float from, float to);




			/* For when 'memoryAddress' contains the actual value. */
			static double GetDouble(const void* memoryPtr);
			static double GetDouble(const uintptr_t& memoryAddress);

			static bool   SetDouble(const void* memoryPtr, double newValue);
			static bool   SetDouble(const uintptr_t& memoryAddress, double newValue);

			static bool   PatchDouble(const void* memoryPtr, double from, double to);
			static bool   PatchDouble(const uintptr_t& memoryAddress, double from, double to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static double IndirectGetDouble(const void* memoryPtr);
			static double IndirectGetDouble(const uintptr_t& memoryAddress);

			static bool   IndirectSetDouble(const void* memoryPtr, double newValue);
			static bool   IndirectSetDouble(const uintptr_t& memoryAddress, double newValue);

			static bool   IndirectPatchDouble(const void* memoryPtr, double from, double to);
			static bool   IndirectPatchDouble(const uintptr_t& memoryAddress, double from, double to);




			/* For when 'memoryAddress' contains the actual value. */
			static std::string GetString(const void* memoryPtr);
			static std::string GetString(const void* memoryPtr, size_t maxLength);
			static std::string GetString(const uintptr_t& memoryAddress);
			static std::string GetString(const uintptr_t& memoryAddress, size_t maxLength);

			static bool		   SetString(const void* memoryPtr, const std::string& newValue);
			static bool		   SetString(const uintptr_t& memoryAddress, const std::string& newValue);

			static bool		   PatchString(const void* memoryPtr, const std::string& from, const std::string& to);
			static bool		   PatchString(const uintptr_t& memoryAddress, const std::string& from, const std::string& to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::string IndirectGetString(const void* memoryPtr);
			static std::string IndirectGetString(const void* memoryPtr, size_t maxLength);
			static std::string IndirectGetString(const uintptr_t& memoryAddress);
			static std::string IndirectGetString(const uintptr_t& memoryAddress, size_t maxLength);

			static bool		   IndirectSetString(const void* memoryPtr, const std::string& newValue);
			static bool		   IndirectSetString(const uintptr_t& memoryAddress, const std::string& newValue);

			static bool		   IndirectPatchString(const void* memoryPtr, const std::string& from, const std::string& to);
			static bool		   IndirectPatchString(const uintptr_t& memoryAddress, const std::string& from, const std::string& to);


			/* For when 'memoryAddress' contains the actual value. */
			static std::wstring GetWString(const void* memoryPtr);
			static std::wstring GetWString(const void* memoryPtr, size_t maxLength);
			static std::wstring GetWString(const uintptr_t& memoryAddress);
			static std::wstring GetWString(const uintptr_t& memoryAddress, size_t maxLength);

			static bool			SetWString(const void* memoryPtr, const std::wstring& newValue);
			static bool			SetWString(const uintptr_t& memoryAddress, const std::wstring& newValue);

			static bool			PatchWString(const void* memoryPtr, const std::wstring& from, const std::wstring& to);
			static bool			PatchWString(const uintptr_t& memoryAddress, const std::wstring& from, const std::wstring& to);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::wstring IndirectGetWString(const void* memoryPtr);
			static std::wstring IndirectGetWString(const void* memoryPtr, size_t maxLength);
			static std::wstring IndirectGetWString(const uintptr_t& memoryAddress);
			static std::wstring IndirectGetWString(const uintptr_t& memoryAddress, size_t maxLength);

			static bool			IndirectSetWString(const void* memoryPtr, const std::wstring& newValue);
			static bool			IndirectSetWString(const uintptr_t& memoryAddress, const std::wstring& newValue);

			static bool			IndirectPatchWString(const void* memoryPtr, const std::wstring& from, const std::wstring& to);
			static bool			IndirectPatchWString(const uintptr_t& memoryAddress, const std::wstring& from, const std::wstring& to);




			/* For when 'memoryAddress' contains the actual value. */
			static std::vector<uint8_t> GetBytes(const void* memoryPtr, size_t byteCount);
			static std::vector<uint8_t> GetBytes(const uintptr_t& memoryAddress, size_t byteCount);

			static bool					SetBytes(const void* memoryPtr, const std::vector<uint8_t>& newBytes);
			static bool					SetBytes(const uintptr_t& memoryAddress, const std::vector<uint8_t>& newBytes);

			static bool					PatchBytes(const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
			static bool					PatchBytes(const uintptr_t& memoryAddress, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);


			/* For when 'memoryAddress' contains the address that leads to the value. */
			static std::vector<uint8_t> IndirectGetBytes(const void* memoryPtr, size_t byteCount);
			static std::vector<uint8_t> IndirectGetBytes(const uintptr_t& memoryAddress, size_t byteCount);

			static bool					IndirectSetBytes(const void* memoryPtr, const std::vector<uint8_t>& newBytes);
			static bool					IndirectSetBytes(const uintptr_t& memoryAddress, const std::vector<uint8_t>& newBytes);

			static bool					IndirectPatchBytes(const void* memoryPtr, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
			static bool					IndirectPatchBytes(const uintptr_t& memoryAddress, const std::vector<uint8_t>& fromBytes, const std::vector<uint8_t>& toBytes);
		};
	}
};

