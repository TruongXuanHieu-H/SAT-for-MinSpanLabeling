#ifndef INCRE_HAS_HOLE_H
#define INCRE_HAS_HOLE_H

#include "incre_vertices_encoder.h"

class IncreHasHole : public IncreVerticesEncoder
{
public:
    IncreHasHole() {};
    ~IncreHasHole() override = default;

    void encode_vertices_constraint(const IncreInstanceData &) override;

    void ignore_label(const IncreInstanceData &, int label) override;

private:
    void force_use_label(const IncreInstanceData &, int label);
};

#endif