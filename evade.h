
typedef LPVOID (WINAPI * pVirtualAllocExNuma) (
  HANDLE         hProcess,
  LPVOID         lpAddress,
  SIZE_T         dwSize,
  DWORD          flAllocationType,
  DWORD          flProtect,
  DWORD          nndPreferred
);

BOOL checkNUMA() {
  LPVOID mem = NULL;
  pVirtualAllocExNuma myVirtualAllocExNuma = (pVirtualAllocExNuma)GetProcAddress(GetModuleHandle("kernel32.dll"), "VirtualAllocExNuma");
  mem = myVirtualAllocExNuma(GetCurrentProcess(), NULL, 1000, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE, 0);
  if (mem != NULL) {
    return false;
  } else {
    return true;
  }
}

BOOL checkResources() {
  SYSTEM_INFO s;
  MEMORYSTATUSEX ms;
  DWORD procNum;
  DWORD ram;

  GetSystemInfo(&s);
  procNum = s.dwNumberOfProcessors;
  if (procNum < 2) return false;

  ms.dwLength = sizeof(ms);
  GlobalMemoryStatusEx(&ms);
  ram = ms.ullTotalPhys / 1024 / 1024 / 1024;
  if (ram < 2) return false;

  return true;
}

BOOL evade() {
  if (checkNUMA() || checkResources()) {
    return false;
  } else {
    return true;
  }
}