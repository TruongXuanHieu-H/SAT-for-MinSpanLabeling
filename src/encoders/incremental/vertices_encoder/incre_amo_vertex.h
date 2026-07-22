#ifndef INCRE_AMO_VERTEX_H
#define INCRE_AMO_VERTEX_H

#include "incre_vertices_encoder.h"

class IncreAMOVertex : public IncreVerticesEncoder
{
public:
    IncreAMOVertex() {};
    ~IncreAMOVertex() override = default;

    void encode_vertices_constraint(const IncreInstanceData &) override;

    void ignore_label(const IncreInstanceData &, int label) override;

private:
    void encode_at_most_one_product(const IncreInstanceData &, const std::vector<int> &vars);
    void encode_amo_seq(const IncreInstanceData &, const std::vector<int> &vars);

    void force_use_label(const IncreInstanceData &, int label);
};

#endif