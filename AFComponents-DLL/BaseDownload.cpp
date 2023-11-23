#include "BaseDownload.h"
#include "BasePath.h"
#include <string>
#include <filesystem>
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void AFC_DownloadA(const char* Url, const char* Path)
{
	if (std::filesystem::exists(Path)) std::filesystem::remove_all(Path);
	char local_path[512] = { 0 };
	AFC_ProgramFolderPathA(local_path, 1024);
	std::filesystem::path cmd_path = local_path;
	cmd_path /= "aria2c.exe";
	std::string command = std::string(" -s 16 -x 16 -o \"") + Path + "\" " + Url;
	STARTUPINFOA si = { 0 };
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESTDHANDLES;
	PROCESS_INFORMATION pi = { 0 };
	CreateProcessA(cmd_path.string().c_str(), &command[0], nullptr, nullptr, 0, 0, nullptr, nullptr, &si, &pi);
	Sleep(100);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void AFC_DownloadW(const wchar_t* Url, const wchar_t* Path)
{
	if (std::filesystem::exists(Path)) std::filesystem::remove_all(Path);
	wchar_t local_path[512] = { 0 };
	AFC_ProgramFolderPathW(local_path, 1024);
	std::filesystem::path cmd_path = local_path;
	cmd_path /= "aria2c.exe";
	std::wstring command = std::wstring(L" -s 16 -x 16 -o \"") + Path + L"\" " + Url;
	STARTUPINFOW si = { 0 };
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESTDHANDLES;
	PROCESS_INFORMATION pi = { 0 };
	CreateProcessW(cmd_path.wstring().c_str(), &command[0], nullptr, nullptr, 0, 0, nullptr, nullptr, &si, &pi);
	Sleep(100);
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
