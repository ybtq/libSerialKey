#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <TMPRSerialKey.h>

#pragma comment(lib, "kernel32.lib")

void SerialKeyTest(const char* secret, unsigned char feature, const char* userInfo = NULL)
{
    int  ret;
    char szBuf[25] = { 0 };

    printf("secret = %s, feature = 0x%02X\n", secret, feature);
    if (userInfo != NULL)
    {
        printf("userInfo = %s\n", userInfo);
    }
    ret = GenerateKey(szBuf, 25, secret, feature, 30, userInfo);
    printf("Generate key : %s\n", szBuf);

    ret = ValidateKey(szBuf, secret, feature, NULL, userInfo);
    printf("Validate key : %s\n", (ret == 0) ? "true" : "false");
    printf("\n");
}

int main(int argc, char *argv[])
{
    argc, argv;

    SerialKeyTest("mpr_fast", 0x01);
    SerialKeyTest("mpr_maker", 0x01);
    SerialKeyTest("mpr_maker", 0x02);

    char    szUserInfo[100] = {0};
    wchar_t szUserInfoW[100] = { 0 };
    strcpy(szUserInfo, "天朗闻听出版社");
    int len = MultiByteToWideChar(CP_ACP, 0, szUserInfo, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, szUserInfo, -1, szUserInfoW, len);
    len = WideCharToMultiByte(CP_UTF8, 0, szUserInfoW, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, szUserInfoW, -1, szUserInfo, len, NULL, NULL);

    SerialKeyTest("mpr_maker", 0x01, szUserInfo);

    // 测试TValidateKey::IsValid()是否在Release版调试状态是否直接返回true.
    int ret = ValidateKey("HMNWE-JBNPH-DMZXG-VBFMZ", "mpr_fast", 0x01, NULL, NULL);
    printf("ValidateKey HMNWE-JBNPH-DMZXG-VBFMZ %s\n", ret == 0 ? "true" : "false");

    system("pause");
}