#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "TMiscUtils.h"

static std::string BASE26_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

unsigned int GetEightByteHash(const std::string& sText, unsigned int nMustBeLessThan)
{
    unsigned int nHash = 0;
    unsigned int nTextLen = (unsigned int)sText.length();

    for (unsigned int i = 0; i < nTextLen; i++)
    {
        nHash += sText[i];
        nHash += (nHash << 10);
        nHash ^= (nHash >> 6);
    }

    nHash += (nHash << 3);
    nHash ^= (nHash >> 11);
    nHash += (nHash << 15);

    unsigned int nResult = (unsigned int)(nHash % nMustBeLessThan);
    unsigned int nCheck = nMustBeLessThan / nResult;

    if (nCheck > 1)
    {
        nResult *= nCheck;
    }
    return nResult;
}

std::string TwentyfiveByteHash(const std::string& sText)
{
    int         nTextLen = (int)sText.length();
    int         nAmountOfBlocks = (nTextLen + 4) / 5;
    char        szBuf[20] = { 0 };
    std::string sHashText;

    for (int i = 0; i < nAmountOfBlocks; i++)
    {
        // linux : error: ‘_ultoa’ was not declared in this scope
        // sHashText += _ultoa(GetEightByteHash(sText.substr(i * 5, 5)), szBuf, 10);
        sprintf(szBuf, "%u", GetEightByteHash(sText.substr(i * 5, 5)));
        sHashText += szBuf;
    }
    return sHashText;
}

std::string Base10ToBase26(const std::string& sText)
{
    std::string     sTemp;
    unsigned int    remainder = 0;
    TBigNumber      bigNumber;

    bigNumber.FromString(sText);
    while (bigNumber >= 26)
    {
        remainder = bigNumber % 26;
        sTemp += BASE26_LETTERS[remainder];
        bigNumber /= 26;
    }
    remainder = bigNumber % 26;
    sTemp += BASE26_LETTERS[remainder];

    return std::string(sTemp.rbegin(), sTemp.rend());
}

std::string Base26ToBase10(const std::string& sText)
{
    TBigNumber  bigNumber;
    TBigNumber  temp;
    int         nTextLen = (unsigned int)sText.length();

    for (int i = 0; i < nTextLen; i++)
    {
        temp.FromPowof(26, nTextLen - i - 1);
        temp *= (unsigned int)BASE26_LETTERS.find(sText.substr(i, 1));
        bigNumber += temp;
    }
    return bigNumber.ToString();
}

std::string EncText(const std::string& sInputPhase, const std::string& sSecretPhase)
{
    int             nTemp = 0;
    unsigned int    nSecretIdx;
    unsigned int    nSecretLen = (unsigned int)sSecretPhase.length();
    std::string     sEncryptedText;    
    char            szBuf[10] = { 0 };

    for (unsigned int i = 0; i < sInputPhase.length(); i++)
    {
        nSecretIdx = Modulo(i, nSecretLen);
        nTemp = Modulo(((sInputPhase[i] - 0x30) + (sSecretPhase[nSecretIdx] - 0x30)), 10);
        sprintf(szBuf, "%u", nTemp);
        sEncryptedText += szBuf;
    }
    return sEncryptedText;
}

std::string DecText(const std::string& sEncryptedPhase, const std::string& sSecretPhase)
{
    int             nTemp = 0;
    unsigned int    nSecretIdx;
    unsigned int    nSecretLen = (unsigned int)sSecretPhase.length();
    std::string     sDecryptedText;
    char            szBuf[10] = { 0 };

    for (unsigned int i = 0; i < sEncryptedPhase.length(); i++)
    {
        nSecretIdx = Modulo(i, nSecretLen);
        nTemp = Modulo(((sEncryptedPhase[i] - 0x30) - (sSecretPhase[nSecretIdx] - 0x30)), 10);
        sprintf(szBuf, "%u", nTemp);
        sDecryptedText += szBuf;
    }
    return sDecryptedText;
}

int Modulo(int nNumber, int nBase)
{
    return nNumber - nBase * (unsigned int)(floor((double)nNumber / nBase));
}

#if defined(ANTI_CRACK) && defined(WIN32)
long IsDebuggerPresent_self()
{
    long nRet = 0;
    // Visual C++ does not support 64-bit inline assembler. 
    // error C4235: nonstandard extension used : '__asm' keyword not supported on this architecture
    // https://social.msdn.microsoft.com/Forums/vstudio/en-US/da4e85c5-407e-4a57-87e7-14bf994504d9/error-asm-keyword-not-supported-on-this-architecture?forum=vcgeneral
#if !defined(_WIN64)
    __asm
    {
        mov     eax, dword ptr fs : [018H];
        mov     eax, dword ptr[eax + 030H];
        movzx   eax, dword ptr[eax + 02H];
        mov     nRet, eax
    }
#endif  
    return nRet;
}
#endif
