#ifndef ITE_VERTICES_ENCODER_H
#define ITE_VERTICES_ENCODER_H

#include "../ite_instance_data.h"

class IteVerticesEncoder
{
public:
    IteVerticesEncoder() = default;
    virtual ~IteVerticesEncoder() = default;

    virtual void encode_vertices_constraint(const IteInstanceData &) = 0;
};

#endif