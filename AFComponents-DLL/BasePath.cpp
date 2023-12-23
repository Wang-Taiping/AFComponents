#pragma warning(disable: 4996)

#include "BasePath.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <filesystem>

namespace afc
{
	AF_EXPORT bool rename(std::filesystem::path Old_p, std::filesystem::path New_p);
}

int AFC_ProgramFilePathA(char* Buffer, int BufSize)
{
	char str[4096] = { 0 };
	GetModuleFileNameA(nullptr, str, 4096);
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) return -1;
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.string().size())
		strcpy(Buffer, path.string().c_str());
	return (path.string().size() + 1);
}

int AFC_ProgramFilePathW(wchar_t* Buffer, int BufSize)
{
	wchar_t str[4096] = { 0 };
	GetModuleFileNameW(nullptr, str, 4096);
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) return -1;
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.wstring().size())
		wcscpy(Buffer, path.wstring().c_str());
	return (path.wstring().size() + 1);
}

int AFC_ProgramFolderPathA(char* Buffer, int BufSize)
{
	char str[4096] = { 0 };
	GetModuleFileNameA(nullptr, str, 4096);
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) return -1;
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.parent_path().string().size())
		strcpy(Buffer, path.parent_path().string().c_str());
	return (path.parent_path().string().size() + 1);
}

int AFC_ProgramFolderPathW(wchar_t* Buffer, int BufSize)
{
	wchar_t str[4096] = { 0 };
	GetModuleFileNameW(nullptr, str, 4096);
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) return -1;
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.parent_path().wstring().size())
		wcscpy(Buffer, path.parent_path().wstring().c_str());
	return (path.parent_path().wstring().size() + 1);
}

int AFC_TempPathA(char* Buffer, int BufSize)
{
	char str[4096] = { 0 };
	int NeedSize = GetEnvironmentVariableA("TEMP", str, 4096);
	if (NeedSize > BufSize) return -1;
	if (GetLastError() == ERROR_ENVVAR_NOT_FOUND) return -1;
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.string().size())
		strcpy(Buffer, path.string().c_str());
	return (path.string().size() + 1);
}

int AFC_TempPathW(wchar_t* Buffer, int BufSize)
{
	wchar_t str[4096] = { 0 };
	int NeedSize = GetEnvironmentVariableW(L"TEMP", str, 4096);
	if (NeedSize > BufSize) return -1;
	if (GetLastError() == ERROR_ENVVAR_NOT_FOUND) return -1;
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.string().size())
		wcscpy(Buffer, path.wstring().c_str());
	return (path.string().size() + 1);
}

int AFC_RenamePathA(const char* Old_p, const char* New_p)
{
	return afc::rename(Old_p, New_p);
}

int AFC_RenamePathW(const wchar_t* Old_p, const wchar_t* New_p)
{
	return afc::rename(Old_p, New_p);
}
