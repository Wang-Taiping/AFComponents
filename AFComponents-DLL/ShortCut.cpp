#include "ShortCut.h"
#include "StringProc.h"
#include <ShlObj.h>

int AFC_CreateShortCutA(const char* FilePath, const char* ShortCutPath, const char* Description, const char* WorkingDir, const char* IconPath, int IconId)
{
	// Create buffer.
	std::wstring szFilePath = afc::convert_string(FilePath);
	std::wstring szShortCutPath = afc::convert_string(ShortCutPath);
	std::wstring szDescription;
	std::wstring szWorkingDir;
	std::wstring szIconPath;
	// Convert string.
	if (Description) szDescription = afc::convert_string(Description);
	if (WorkingDir) szWorkingDir = afc::convert_string(WorkingDir);
	if (IconPath) szIconPath = afc::convert_string(IconPath);
	// Create shortcut and return.
	return AFC_CreateShortCutW(
		szFilePath.c_str(),
		szShortCutPath.c_str(),
		(szDescription.empty()) ? nullptr : szDescription.c_str(),
		(szWorkingDir.empty()) ? nullptr : szWorkingDir.c_str(),
		(szIconPath.empty()) ? nullptr : szIconPath.c_str(),
		IconId);
}

int AFC_CreateShortCutW(const wchar_t* FilePath, const wchar_t* ShortCutPath, const wchar_t* Description, const wchar_t* WorkingDir, const wchar_t* IconPath, int IconId)
{
	int nReturn = 1;
	IShellLink* pIShellLink = nullptr;
	IPersistFile* pIPersistFile = nullptr;
	try
	{
		HRESULT hr = ::CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER,
			IID_IShellLink, (void**)&pIShellLink);
		if (!SUCCEEDED(hr))
			throw "create shell_link object fail.";
		hr = pIShellLink->SetPath(FilePath);
		if (!SUCCEEDED(hr))
			throw "set target fail";
		if (Description)
		{
			hr = pIShellLink->SetDescription(Description);
			if (!SUCCEEDED(hr))
				throw "set description fail.";
		}
		if (WorkingDir)
		{
			hr = pIShellLink->SetWorkingDirectory(WorkingDir);
			if (!SUCCEEDED(hr))
				throw "set working_directory fail.";
		}
		if (IconPath)
		{
			hr = pIShellLink->SetIconLocation(IconPath, IconId);
			if (!SUCCEEDED(hr))
				throw "set icon fail.";
		}
		hr = pIShellLink->QueryInterface(IID_IPersistFile, (void**)&pIPersistFile);
		if (!SUCCEEDED(hr))
			throw "create save object fail.";
		hr = pIPersistFile->Save(ShortCutPath, TRUE);
		if (!SUCCEEDED(hr))
			throw "save fail.";
	}
	catch (...) { nReturn = 0; }
	if (pIPersistFile) pIPersistFile->Release();
	if (pIShellLink) pIShellLink->Release();
	return nReturn;
}
