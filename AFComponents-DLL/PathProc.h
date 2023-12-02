#pragma once

#ifndef AFPATHPROC_H
#define AFPATHPROC_H

#include "BaseLibrary.h"
#include "BasePath.h"

#ifdef __cplusplus

#if _HAS_CXX17

#include <filesystem>

namespace afc
{
	std::filesystem::path program_path();
	std::filesystem::path program_dir_path();
	std::filesystem::path temp_path();
}

#endif // _HAS_CXX17

#endif // __cplusplus

#endif // !AFPATHPROC_H
