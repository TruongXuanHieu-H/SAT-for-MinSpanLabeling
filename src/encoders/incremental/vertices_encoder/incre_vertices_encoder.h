#ifndef INCRE_VERTICES_ENCODER_H
#define INCRE_VERTICES_ENCODER_H

#include "../incre_instance_data.h"

class IncreVerticesEncoder
{
public:
    IncreVerticesEncoder() = default;
    virtual ~IncreVerticesEncoder() = default;

    virtual void encode_vertices_constraint(const IncreInstanceData &) = 0;

    virtual void ignore_label(const IncreInstanceData &, int label) = 0;
};

#endif