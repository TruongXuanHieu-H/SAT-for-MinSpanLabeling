#include "ite_encoder.h"
#include "ite_instance_data.h"
#include "../../global_data.h"
#include <iostream>

IteEncoder::IteEncoder(IteInstanceData &instance_data) : instance_data(instance_data) {}
IteEncoder::~IteEncoder() {}

void IteEncoder::encode_symmetry_break()
{
    if (instance_data.global_data.symmetry_break_strategy == SymmetryBreakingType::FIRST)
    {
        encode_symmetry_break_first_node();
    }
    else if (instance_data.global_data.symmetry_break_strategy == SymmetryBreakingType::HIGHEST_DEGREE)
    {
        encode_symmetry_break_highest_degree_node();
    }
    else if (instance_data.global_data.symmetry_break_strategy == SymmetryBreakingType::LOWEST_DEGREE)
    {
        encode_symmetry_break_lowest_degree_node();
    }
    else
    {
        // No symmetry breaking
    }
}

void IteEncoder::encode_symmetry_break_first_node()
{
    for (int i = instance_data.label; i > instance_data.label - (instance_data.label / 2); i--)
    {
        instance_data.cc->add_clause({-1 * int(i)});
    }
}

void IteEncoder::encode_symmetry_break_highest_degree_node()
{
    int max_node_id = instance_data.global_data.g->find_greatest_outdegree_node();

    for (int i = max_node_id * instance_data.label; i > (max_node_id * instance_data.label) - (instance_data.label / 2); i--)
    {
        instance_data.cc->add_clause({-1 * int(i)});
    }
}

void IteEncoder::encode_symmetry_break_lowest_degree_node()
{
    int min_node_id = instance_data.global_data.g->find_smallest_outdegree_node();

    for (int i = min_node_id * instance_data.label; i > (min_node_id * instance_data.label) - (instance_data.label / 2); i--)
    {
        instance_data.cc->add_clause({-1 * int(i)});
    }
}