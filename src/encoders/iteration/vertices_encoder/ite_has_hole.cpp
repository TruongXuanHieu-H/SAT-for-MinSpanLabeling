#include "ite_has_hole.h"

#include <vector>

void IteHasHole::encode_vertices_constraint(const IteInstanceData &instance_data)
{
    force_use_label(instance_data, 0);
}

void IteHasHole::force_use_label(const IteInstanceData &instance_data, int label)
{
    std::vector<int> node_vertices(instance_data.global_data.g.n);

    for (int vertex = 0; vertex < instance_data.global_data.g.n; vertex++)
        node_vertices[vertex] = vertex * instance_data.global_data.upper_bound + label + 1;

    instance_data.cc->add_clause(node_vertices);
}