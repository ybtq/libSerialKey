#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "TGenerateKey.h"
#include "TMiscUtils.h"

TGenerateKey::TGenerateKey(const std::string& sSecretPhase, unsigned char feature)
: TBaseConfiguration(sSecretPhase, feature)
{
}

bool TGenerateKey::EncodeKey(std::string& sKey, unsigned int nDays, const std::string sUserInfo)
{
    if (nDays > 999)
    {
        return false;
    }
    unsigned int nId = 0;
    
    if (!sUserInfo.empty())
    {
        nId = GetEightByteHash(sUserInfo, 100000);
    }
    else
    {
        // Seed the random-number generator with current time so that
        // the numbers will be different every time we run.
        srand((unsigned)time(NULL));
        nId = rand() % 100000;
    }
    std::string sText = Encrypt(nDays, nId, time(NULL));

    unsigned int nBlockCount = (unsigned int)sText.length() / 5;
    unsigned int i;
    sKey.clear();
    for (i = 0; i < nBlockCount - 1; i++)
    {
        sKey += sText.substr(i * 5, 5) + "-";
    }
    sKey += sText.substr(i * 5);
    return true;
}

std::string TGenerateKey::Encrypt(unsigned int nDays, unsigned int nId, time_t createTime)
{
    TBigNumber bigNumber;

    // e.g. "20160704"
    char szBuf[20] = {0};
    tm* tmCreate = localtime(&createTime);
    strftime(szBuf, 9, "%Y%m%d", tmCreate);

    unsigned int nCreateDate = strtoul(szBuf, NULL, 10);
    bigNumber += nCreateDate;

    bigNumber *= 1000;
    bigNumber += nDays;

    bigNumber *= 1000;
    bigNumber += (unsigned int)mFeature;

    bigNumber *= 100000;
    bigNumber += nId;

    std::string sNumberText = bigNumber.ToString();
    std::string sText;
    sprintf(szBuf, "%u", GetEightByteHash(sNumberText));
    sText = szBuf;
    if (msSecretPhase.empty())
    {
        sText += sNumberText;
    }
    else
    {
        sText += EncText(sNumberText, msSecretPhase);
    }
    return Base10ToBase26(sText);
}
