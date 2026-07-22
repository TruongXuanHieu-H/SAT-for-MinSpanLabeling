#ifndef ITE_HAS_HOLE_H
#define ITE_HAS_HOLE_H

#include "ite_vertices_encoder.h"

class IteHasHole : public IteVerticesEncoder
{
public:
    IteHasHole() {};
    ~IteHasHole() override = default;

    void encode_vertices_constraint(const IteInstanceData &) override;

private:
    void force_use_label(const IteInstanceData &, int label);
};

#endif