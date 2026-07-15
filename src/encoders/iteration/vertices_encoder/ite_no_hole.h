#ifndef ITE_NO_HOLE_H
#define ITE_NO_HOLE_H

#include "ite_vertices_encoder.h"

class IteNoHole : public IteVerticesEncoder
{
public:
    IteNoHole() {};
    ~IteNoHole() override = default;

    void encode_vertices_constraint(const IteInstanceData &) override;
};

#endif