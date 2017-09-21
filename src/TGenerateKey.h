#include "TBaseConfiguration.h"

class TGenerateKey : public TBaseConfiguration
{
public:
    TGenerateKey(const std::string& sSecretPhase, unsigned char feature);

    // nDays : Available days(e.g. 30), if days is 0, the serial key is long-term.
    // sUserInfo : User information(e.g. username). if sUserInfo is empty, generate random serial key.
    bool        EncodeKey(std::string& sKey, unsigned int nDays, const std::string sUserInfo = std::string());

protected:
    std::string Encrypt(unsigned int nDays, unsigned int nId, time_t createTime);
};