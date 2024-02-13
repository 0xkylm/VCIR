#include "fun.h"

int returnx2(char *fmt, ...) {
  va_list ap;
  int d;
  char c;
  char *s;

  va_start(ap, fmt);
  while (*fmt)
    switch (*fmt++) {
    case 's':
      s = va_arg(ap, char *);
      printf("string %s\n", s);
      break;
    case 'd':
      d = va_arg(ap, int);
      printf("int %d\n", d);
      break;
    case 'c':

      c = (char)va_arg(ap, int);
      printf("char %c\n", c);
      break;
    }
  va_end(ap);
  return d * d;
}
void where_hook() {}

void printAAAA() { printf("AAAAAAAA\n"); }

char *HandleOn(const char *name) {

  // return name;
}

int IsElevated() {
  int fRet = 0;
  HANDLE hToken = NULL;
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
    TOKEN_ELEVATION Elevation = {0};
    DWORD cbSize = sizeof(TOKEN_ELEVATION);
    if (GetTokenInformation(hToken, TokenElevation, &Elevation,
                            sizeof(Elevation), &cbSize)) {
      fRet = Elevation.TokenIsElevated;
      // printf("fRet = %d\n",fRet);
    }
  }
  if (hToken) {
    CloseHandle(hToken);
  }
  return fRet;
}

void call(const char cmd[]) { system(cmd); }

void GetToken(const char PrivName[]) {
  HANDLE hToken;
  LUID luid;
  TOKEN_PRIVILEGES tkp;

  OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                   &hToken);

  LookupPrivilegeValue(NULL, PrivName, &luid);

  tkp.PrivilegeCount = 1;
  tkp.Privileges[0].Luid = luid;
  tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

  AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);

  CloseHandle(hToken);
}

void ChangeRegKey(char ap[]) {
  // Curently use for print the string

  //    va_list ap;
  //    int d;
  //    char c;
  //    char *s;

  //    va_start(ap, fmt);

  printf("%s\n", ap);

  // HKEY key;
  // HKEY new_key;
  // DWORD disable = -1;
  // //LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
  // "SOFTWARE\\Policies\\Microsoft\\Windows Defender", 0, KEY_ALL_ACCESS,
  // &key); LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, ap[0] , 0,
  // KEY_ALL_ACCESS, &key);

  // if (res == ERROR_SUCCESS) {
  //    // res = RegSetValueEx(key, "DisableAntiSpyware", 0, REG_DWORD, (const
  //    BYTE*)&disable, sizeof(disable));

  //     if (res == ERROR_SUCCESS) {
  //         //res = RegCreateKeyEx(key, "Real-Time Protection", 0, 0,
  //         REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &new_key, 0);

  //         if (res == ERROR_SUCCESS) {
  //             //res = RegSetValueEx(new_key, "DisableRealtimeMonitoring", 0,
  //             REG_DWORD, (const BYTE*)&disable, sizeof(disable));
  //             //res = RegSetValueEx(new_key, "DisableBehaviorMonitoring", 0,
  //             REG_DWORD, (const BYTE*)&disable, sizeof(disable));
  //             //res = RegSetValueEx(new_key, "DisableScanOnRealtimeEnable",
  //             0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
  //             //res = RegSetValueEx(new_key, "DisableOnAccessProtection", 0,
  //             REG_DWORD, (const BYTE*)&disable, sizeof(disable));
  //             //res = RegSetValueEx(new_key, "DisableIOAVProtection", 0,
  //             REG_DWORD, (const BYTE*)&disable, sizeof(disable));
  //             RegCloseKey(new_key);
  //         }
  //     }

  //     RegCloseKey(key);
  // }

  // va_end(ap);
}

// void printAAAA(){
//     printf("AAAAAAAA\n");
// }
