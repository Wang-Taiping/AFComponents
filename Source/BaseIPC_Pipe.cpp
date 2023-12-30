#include "BaseIPC.h"
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define AFC_PIPE_PREFIXA	R"(\\.\pipe\)"
#define AFC_PIPE_PREFIXW	LR"(\\.\pipe\)"

int AFC_IsPipeExistsA(const char* PipeName, int MilliSec)
{
	std::string name = AFC_PIPE_PREFIXA;
	name += PipeName;
	while (MilliSec > 200)
	{
		if (WaitNamedPipeA(name.c_str(), 1)) return true;
		Sleep(199);
		MilliSec -= 200;
	}
	Sleep(MilliSec - 1);
	return WaitNamedPipeA(name.c_str(), 1);
}

int AFC_IsPipeExistsW(const wchar_t* PipeName, int MilliSec)
{
	std::wstring name = AFC_PIPE_PREFIXW;
	name += PipeName;
	while (MilliSec > 200)
	{
		if (WaitNamedPipeW(name.c_str(), 1)) return true;
		Sleep(199);
		MilliSec -= 200;
	}
	Sleep(MilliSec - 1);
	return WaitNamedPipeW(name.c_str(), 1);
}

AFC_PIPE AFC_CreatePipeA(const char* PipeName, int PipeMode)
{
	if (!(PipeMode & AFC_PIPE_ACCESS_ALL)) return nullptr;
	std::string name = AFC_PIPE_PREFIXA;
	name += PipeName;
	AFC_PIPE hPipe = CreateNamedPipeA(name.c_str(), DWORD(PipeMode) | FILE_FLAG_FIRST_PIPE_INSTANCE, PIPE_WAIT | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 4096, 4096, 0, nullptr);
	return (hPipe == INVALID_HANDLE_VALUE) ? nullptr : hPipe;
}

AFC_PIPE AFC_CreatePipeW(const wchar_t* PipeName, int PipeMode)
{
	if (!(PipeMode & AFC_PIPE_ACCESS_ALL)) return nullptr;
	std::wstring name = AFC_PIPE_PREFIXW;
	name += PipeName;
	AFC_PIPE hPipe = CreateNamedPipeW(name.c_str(), DWORD(PipeMode) | FILE_FLAG_FIRST_PIPE_INSTANCE, PIPE_WAIT | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, 1, 4096, 4096, 0, nullptr);
	return (hPipe == INVALID_HANDLE_VALUE) ? nullptr : hPipe;
}

int AFC_OpenPipe(AFC_PIPE PipeHandle)
{
	return ConnectNamedPipe(PipeHandle, nullptr);
}

void AFC_ClosePipe(AFC_PIPE PipeHandle)
{
	DisconnectNamedPipe(PipeHandle);
}

AFC_PIPE AFC_ConnectPipeA(const char* PipeName, int PipeMode)
{
	if (!(PipeMode & AFC_PIPE_ACCESS_ALL)) return nullptr;
	std::string name = AFC_PIPE_PREFIXA;
	name += PipeName;
	DWORD Permission = 0;
	if (PipeMode & AFC_PIPE_ACCESS_READ) Permission |= GENERIC_READ;
	if (PipeMode & AFC_PIPE_ACCESS_WRITE) Permission |= GENERIC_WRITE;
	AFC_PIPE hPipe = CreateFileA(name.c_str(), Permission, 0, nullptr, OPEN_EXISTING, 0, nullptr);
	return (hPipe == INVALID_HANDLE_VALUE) ? nullptr : hPipe;
}

AFC_PIPE AFC_ConnectPipeW(const wchar_t* PipeName, int PipeMode)
{
	if (!(PipeMode & AFC_PIPE_ACCESS_ALL)) return nullptr;
	std::wstring name = AFC_PIPE_PREFIXW;
	name += PipeName;
	DWORD Permission = 0;
	if (PipeMode & AFC_PIPE_ACCESS_READ) Permission |= GENERIC_READ;
	if (PipeMode & AFC_PIPE_ACCESS_WRITE) Permission |= GENERIC_WRITE;
	AFC_PIPE hPipe = CreateFileW(name.c_str(), Permission, 0, nullptr, OPEN_EXISTING, 0, nullptr);
	return (hPipe == INVALID_HANDLE_VALUE) ? nullptr : hPipe;
}

void AFC_DestroyPipe(AFC_PIPE PipeHandle)
{
	CloseHandle(PipeHandle);
}
