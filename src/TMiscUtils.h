#include <string>
#include "TBigNumber.h"


unsigned int    GetEightByteHash(const std::string& sText, unsigned int nMustBeLessThan = 1000000000);
std::string     TwentyfiveByteHash(const std::string& sText);

std::string     Base10ToBase26(const std::string& sText);
std::string     Base26ToBase10(const std::string& sText);

std::string     EncText(const std::string& sInputPhase, const std::string& sSecretPhase);
std::string     DecText(const std::string& sEncryptedPhase, const std::string& sSecretPhase);

int             Modulo(int nNumber, int nBase);

#if defined(ANTI_CRACK) && defined(WIN32)
long            IsDebuggerPresent_self();
#endif