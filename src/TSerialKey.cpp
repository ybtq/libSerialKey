#include <string.h>
#include "../include/TSerialKey.h"
#include "TGenerateKey.h"
#include "TValidateKey.h"

int GenerateKey(char* key, int keyLen, const char* secret, unsigned char feature,
    int days, const char* userInfo)
{
    if (key == NULL || secret == NULL || days < 0 || days > 999)
    {
        return -1;
    }
    TGenerateKey generate(secret, feature);
    std::string sUserInfo;
    if (userInfo != NULL)
    {
        sUserInfo = userInfo;
    }
    std::string sKey;
    if (!generate.EncodeKey(sKey, days, sUserInfo) 
        || (unsigned int)keyLen < sKey.length())
    {
        return -1;
    }
    strncpy(key, sKey.c_str(), keyLen);
    return 0;
}

int ValidateKey(const char* key, const char* secret, unsigned char feature,
    int* days, const char* userInfo)
{
    if (key == NULL || secret == NULL)
    {
        return -1;
    }
    TValidateKey validate(secret, feature);
    std::string sUserInfo;
    if (userInfo != NULL)
    {
        sUserInfo = userInfo;
    }
    if (!validate.DecodeKey(key, sUserInfo))
    {
        return -1;
    }
    if (days != NULL)
    {
        *days = validate.Days();
    }
    return validate.IsValid() ? 0 : -1;
}


#if 0 //defined(_WINDLL)
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  dwReason, LPVOID /*lpReserved*/)
{
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        ::DisableThreadLibraryCalls((HMODULE)hModule);
        break;
    }
    return TRUE;
}
#endif 
