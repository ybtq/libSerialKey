#include "TBaseConfiguration.h"

class TValidateKey : public TBaseConfiguration
{
public:
    TValidateKey(const std::string& sSecretPhase, unsigned char feature);

    // sKey : Serial key.
    // sUserInfo : User information(e.g. username). if sUserInfo is empty, it would not verify user information.
    bool            DecodeKey(const std::string& sKey, const std::string& sUserInfo = std::string());

    // Serial key is valid or not.
    bool            IsValid();

    // Available days(e.g. 30), if days is 0, the serial key is long-term.
    unsigned int    Days();

protected:
    bool            Decrypt(const std::string& sEncryptedText);

private:
    bool            mbValid;
    bool            mbDebuggerPresent;
    unsigned int    mnDays;
    unsigned int    mnUserId;
};