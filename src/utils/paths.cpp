#include <pch.h>
#include "paths.h"

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
//#pragma comment(lib, "shell32.lib")
std::string utils::GetUserDataPath() {
    char path[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(nullptr, CSIDL_LOCAL_APPDATA, nullptr, 0, path))) {
        std::string dir = std::string(path) + "\\CoasterBuilder\\";
        std::filesystem::create_directories(dir); // ensures the folder exists
        return dir;
    }
    return ".\\";
}
#endif

// FIXME: Implement for linux (and maybe macOS ?)
