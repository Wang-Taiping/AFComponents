#include "PathProc.h"

namespace fs = std::filesystem;

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

bool afc::rename(std::filesystem::path Old_p, std::filesystem::path New_p)
{
	std::error_code ec;
	if (!fs::exists(Old_p, ec)) return false;
	if (!fs::exists(New_p, ec))
	{
		fs::create_directories(New_p.parent_path(), ec);
		fs::rename(Old_p, New_p, ec);
		return true;
	}
	if (fs::is_directory(Old_p))
	{
		if (!fs::exists(New_p)) fs::create_directory(New_p);
		for (auto i : fs::directory_iterator(Old_p, ec))
			::afc::rename(i.path(), New_p / i.path().filename());
		fs::remove_all(Old_p);
	}
	else
	{
		if (fs::exists(New_p)) fs::remove_all(New_p);
		fs::rename(Old_p, New_p, ec);
		return !bool(ec);
	}
	return true;
}
