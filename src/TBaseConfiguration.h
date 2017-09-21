#ifndef _TBASECONFIGURATION_H_
#define _TBASECONFIGURATION_H_

#include <string>
#include "TBigNumber.h"

class TBaseConfiguration
{
public:
    TBaseConfiguration(const std::string& sSecrect, unsigned char feature);

protected:
    unsigned char   mFeature;
    std::string     msSecretPhase;
};

#endif // _TBASECONFIGURATION_H_
