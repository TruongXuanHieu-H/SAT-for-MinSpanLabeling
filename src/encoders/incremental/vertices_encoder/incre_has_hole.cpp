#include "incre_has_hole.h"

#include <vector>

void IncreHasHole::encode_vertices_constraint(const IncreInstanceData &instance_data)
{
    force_use_label(instance_data, 0);
}

void IncreHasHole::ignore_label(const IncreInstanceData &instance_data, int label)
{
    for (int j = 0; j < instance_data.global_data.g.n; j++)
    {
        instance_data.cc->add_clause({-(j * instance_data.global_data.upper_bound + label)});
    }
}

void IncreHasHole::force_use_label(const IncreInstanceData &instance_data, int label)
{
    std::vector<int> node_vertices(instance_data.global_data.g.n);

    for (int vertex = 0; vertex < instance_data.global_data.g.n; vertex++)
        node_vertices[vertex] = vertex * instance_data.global_data.upper_bound + label + 1;

    instance_data.cc->add_clause(node_vertices);
}