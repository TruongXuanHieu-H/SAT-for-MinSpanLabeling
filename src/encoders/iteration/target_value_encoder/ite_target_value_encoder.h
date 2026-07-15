#ifndef ITE_TARGET_VALUE_ENCODER_H
#define ITE_TARGET_VALUE_ENCODER_H

#include "../ite_instance_data.h"

class IteTargetValueEncoder
{
public:
    IteTargetValueEncoder() = default;
    virtual ~IteTargetValueEncoder() = default;

    virtual void encode_target_value(const IteInstanceData &) = 0;

    virtual void encode_labels(const IteInstanceData &) = 0;
};

#endif