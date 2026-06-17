#include "incre_encoder.h"
#include "incre_instance_data.h"
#include "../../global_data.h"
#include <iostream>

IncreEncoder::IncreEncoder(IncreInstanceData &instance_data) : instance_data(instance_data) {}
IncreEncoder::~IncreEncoder() {}

void IncreEncoder::encode_symmetry_break()
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

void IncreEncoder::encode_symmetry_break_first_node()
{
    std::cout << "c " << instance_data.get_signature() << " Symmetry breaking first node is applied.\n";
    for (int i = instance_data.global_data.upper_bound; i > instance_data.global_data.upper_bound - (instance_data.global_data.upper_bound / 2); i--)
    {
        instance_data.cc->add_clause({-1 * int(i)});
    }
}

void IncreEncoder::encode_symmetry_break_highest_degree_node()
{
    std::cout << "c " << instance_data.get_signature() << " Symmetry breaking highest degree node is applied.\n";
    int max_node_id = instance_data.global_data.g->find_greatest_outdegree_node();

    for (int i = max_node_id * instance_data.global_data.upper_bound; i > (max_node_id * instance_data.global_data.upper_bound) - (instance_data.global_data.upper_bound / 2); i--)
    {
        instance_data.cc->add_clause({-1 * int(i)});
    }
}

void IncreEncoder::encode_symmetry_break_lowest_degree_node()
{
    std::cout << "c " << instance_data.get_signature() << " Symmetry breaking lowest degree node is applied.\n";
    int min_node_id = instance_data.global_data.g->find_smallest_outdegree_node();

    for (int i = min_node_id * instance_data.global_data.upper_bound; i > (min_node_id * instance_data.global_data.upper_bound) - (instance_data.global_data.upper_bound / 2); i--)
    {
        instance_data.cc->add_clause({-1 * int(i)});
    }
}