#ifndef INCRE_TARGET_VALUE_ENCODER_H
#define INCRE_TARGET_VALUE_ENCODER_H

#include "../incre_instance_data.h"

class IncreTargetValueEncoder
{
public:
    IncreTargetValueEncoder() = default;
    virtual ~IncreTargetValueEncoder() = default;

    virtual void encode_target_value(const IncreInstanceData &) = 0;

    virtual void encode_labels(const IncreInstanceData &) = 0;
};

#endif