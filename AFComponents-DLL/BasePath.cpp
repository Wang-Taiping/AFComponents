#pragma warning(disable: 4996)

#include "BasePath.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <filesystem>

int AFC_ProgramFilePathA(char* Buffer, int BufSize)
{
	char str[4096] = { 0 };
	GetModuleFileNameA(nullptr, str, 4096);
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.string().size())
		strcpy(Buffer, path.string().c_str());
	return (path.string().size() + 1);
}

int AFC_ProgramFilePathW(wchar_t* Buffer, int BufSize)
{
	wchar_t str[4096] = { 0 };
	GetModuleFileNameW(nullptr, str, 4096);
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.wstring().size())
		wcscpy(Buffer, path.wstring().c_str());
	return (path.wstring().size() + 1);
}

int AFC_ProgramFolderPathA(char* Buffer, int BufSize)
{
	char str[4096] = { 0 };
	GetModuleFileNameA(nullptr, str, 4096);
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.parent_path().string().size())
		strcpy(Buffer, path.parent_path().string().c_str());
	return (path.parent_path().string().size() + 1);
}

int AFC_ProgramFolderPathW(wchar_t* Buffer, int BufSize)
{
	wchar_t str[4096] = { 0 };
	GetModuleFileNameW(nullptr, str, 4096);
	std::filesystem::path path = std::filesystem::absolute(str);
	if (Buffer && BufSize > path.parent_path().wstring().size())
		wcscpy(Buffer, path.parent_path().wstring().c_str());
	return (path.parent_path().wstring().size() + 1);
}
