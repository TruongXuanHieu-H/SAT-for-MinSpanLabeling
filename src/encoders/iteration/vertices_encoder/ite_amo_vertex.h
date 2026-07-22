#ifndef ITE_AMO_VERTEX_H
#define ITE_AMO_VERTEX_H

#include "ite_vertices_encoder.h"

class IteAMOVertex : public IteVerticesEncoder
{
public:
    IteAMOVertex() {};
    ~IteAMOVertex() override = default;

    void encode_vertices_constraint(const IteInstanceData &) override;

private:
    void encode_at_most_one_product(const IteInstanceData &, const std::vector<int> &vars);
    void encode_amo_seq(const IteInstanceData &, const std::vector<int> &vars);

    void force_use_label(const IteInstanceData &, int label);
};

#endif