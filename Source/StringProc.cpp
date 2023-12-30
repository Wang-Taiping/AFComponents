#include "StringProc.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

std::string afc::convert_string(std::wstring string)
{
    int len = WideCharToMultiByte(65001, 0, string.c_str(), string.size() + 1, nullptr, 0, nullptr, nullptr);
    char* buf = new char[len];
    memset(buf, 0, len);
    len = WideCharToMultiByte(65001, 0, string.c_str(), string.size() + 1, buf, len, nullptr, nullptr);
    std::string ret = buf;
    delete[] buf;
    return ret;
}

std::wstring afc::convert_string(std::string string)
{
    int len = MultiByteToWideChar(936, 0, string.c_str(), string.size() + 1, nullptr, 0);
    wchar_t* buf = new wchar_t[len];
    memset(buf, 0, len * sizeof(wchar_t));
    len = MultiByteToWideChar(936, 0, string.c_str(), string.size() + 1, buf, len);
    std::wstring ret = buf;
    delete[] buf;
    return ret;
}

bool afc::match_head(std::string string, std::string pattern)
{
    return string.find(pattern) == 0;
}

bool afc::match_tail(std::string string, std::string pattern)
{
    return string.rfind(pattern) == string.size() - pattern.size();
}
