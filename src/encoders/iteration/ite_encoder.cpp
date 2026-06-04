#include "ite_encoder.h"
#include "ite_instance_data.h"
#include "../../global_data.h"
#include <iostream>

IteEncoder::IteEncoder() {}
IteEncoder::~IteEncoder() {}

void IteEncoder::encode_symmetry_break()
{
    if (GlobalData::symmetry_break_strategy == SymmetryBreakingType::FIRST)
    {
        encode_symmetry_break_first_node();
    }
    else if (GlobalData::symmetry_break_strategy == SymmetryBreakingType::HIGHEST_DEGREE)
    {
        encode_symmetry_break_highest_degree_node();
    }
    else if (GlobalData::symmetry_break_strategy == SymmetryBreakingType::LOWEST_DEGREE)
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
    std::cout << "c " << IteInstanceData::get_signature() << " Symmetry breaking first node is applied.\n";
    for (int i = GlobalData::g->n; i > GlobalData::g->n - (GlobalData::g->n / 2); i--)
    {
        IteInstanceData::cc->add_clause({-1 * int(i)});
    }
}

void IteEncoder::encode_symmetry_break_highest_degree_node()
{
    std::cout << "c " << IteInstanceData::get_signature() << " Symmetry breaking highest degree node is applied.\n";
    int max_node_id = GlobalData::g->find_greatest_outdegree_node();

    for (int i = max_node_id * GlobalData::g->n; i > (max_node_id * GlobalData::g->n) - (GlobalData::g->n / 2); i--)
    {
        IteInstanceData::cc->add_clause({-1 * int(i)});
    }
}

void IteEncoder::encode_symmetry_break_lowest_degree_node()
{
    std::cout << "c " << IteInstanceData::get_signature() << " Symmetry breaking lowest degree node is applied.\n";
    int min_node_id = GlobalData::g->find_smallest_outdegree_node();

    for (int i = min_node_id * GlobalData::g->n; i > (min_node_id * GlobalData::g->n) - (GlobalData::g->n / 2); i--)
    {
        IteInstanceData::cc->add_clause({-1 * int(i)});
    }
}