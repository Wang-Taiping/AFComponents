
// Section Download

#ifdef _DEBUG
#pragma comment(lib, "../lib_debug/libcurl.lib")
#endif // _DEBUG

#ifdef NDEBUG
#pragma comment(lib, "../lib_release/libcurl.lib")
#endif // NDEBUG

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Normaliz.lib")