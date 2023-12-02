#include "PathProc.h"

std::filesystem::path afc::program_path()
{
	wchar_t path[4096] = { 0 };
	if (AFC_ProgramFilePathW(path, 4096) == int(-1)) return std::filesystem::path();
	return path;
}

std::filesystem::path afc::program_dir_path()
{
	return program_path().parent_path();
}

std::filesystem::path afc::temp_path()
{
	wchar_t path[4096] = { 0 };
	if (AFC_TempPathW(path, 4096) == int(-1)) return std::filesystem::path();
	return path;
}
