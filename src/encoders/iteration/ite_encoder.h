#ifndef ITE_ENCODER_H
#define ITE_ENCODER_H

#include "vertices_encoder/ite_amo_vertex.h"
#include "vertices_encoder/ite_has_hole.h"
#include "vertices_encoder/ite_no_hole.h"

#include "target_value_encoder/ite_ladder_abp.h"
#include "target_value_encoder/ite_ladder_cabp.h"

#include <memory>

class IteInstanceData;

class IteEncoder
{
public:
    IteEncoder(IteInstanceData &instance_data);
    ~IteEncoder();

    void encode_min_makespan_labeling();

protected:
    IteInstanceData &instance_data;

    std::unique_ptr<IteVerticesEncoder> vertices_encoder;
    std::unique_ptr<IteTargetValueEncoder> target_value_encoder;

    void encode_symmetry_break();

private:
    void encode_symmetry_break_first_node();
    void encode_symmetry_break_highest_degree_node();
    void encode_symmetry_break_lowest_degree_node();
};

#endif // ITE_ENCODER_H