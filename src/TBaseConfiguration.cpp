#include "TBaseConfiguration.h"
#include "TMiscUtils.h"

TBaseConfiguration::TBaseConfiguration(const std::string& sSecrect, unsigned char feature)
{
    if (sSecrect != msSecretPhase)
    {
        msSecretPhase = TwentyfiveByteHash(sSecrect);
    }
    mFeature = feature;
}