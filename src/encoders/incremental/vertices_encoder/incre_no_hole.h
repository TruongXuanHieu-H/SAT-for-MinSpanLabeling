#ifndef INCRE_NO_HOLE_H
#define INCRE_NO_HOLE_H

#include "incre_vertices_encoder.h"

class IncreNoHole : public IncreVerticesEncoder
{
public:
    IncreNoHole() {};
    ~IncreNoHole() override = default;

    void encode_vertices_constraint(const IncreInstanceData &) override;

    void ignore_label(const IncreInstanceData &, int label) override;

protected:
    std::vector<int> no_hole_incre_aux_var;
};

#endif