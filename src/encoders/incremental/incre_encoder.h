#ifndef INCRE_ENCODER_H
#define INCRE_ENCODER_H

#include "vertices_encoder/incre_amo_vertex.h"
#include "vertices_encoder/incre_has_hole.h"
#include "vertices_encoder/incre_no_hole.h"

#include "target_value_encoder/incre_ladder_abp.h"

#include <memory>

class IncreInstanceData;

class IncreEncoder
{
public:
    IncreEncoder(IncreInstanceData &instance_data);
    ~IncreEncoder();

    void encode_min_makespan_labeling();

    void ignore_label(int ignored_label);

protected:
    IncreInstanceData &instance_data;

    std::unique_ptr<IncreVerticesEncoder> vertices_encoder;
    std::unique_ptr<IncreTargetValueEncoder> target_value_encoder;

    void encode_symmetry_break();

private:
    void encode_symmetry_break_first_node();
    void encode_symmetry_break_highest_degree_node();
    void encode_symmetry_break_lowest_degree_node();
};

#endif