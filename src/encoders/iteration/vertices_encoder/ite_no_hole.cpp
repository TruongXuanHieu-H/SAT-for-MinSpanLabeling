#include "ite_no_hole.h"

#include <vector>

void IteNoHole::encode_vertices_constraint(const IteInstanceData &instance_data)
{
    for (int label = 0; label < instance_data.label; label++)
    {
        std::vector<int> node_vertices(instance_data.global_data.g->n);

        for (int vertex = 0; vertex < instance_data.global_data.g->n; vertex++)
        {
            node_vertices[vertex] = vertex * instance_data.label + label + 1;
        }

        instance_data.cc->add_clause(node_vertices);
    }
}