#include "incre_no_hole.h"

#include <vector>

void IncreNoHole::encode_vertices_constraint(const IncreInstanceData &instance_data)
{
    no_hole_incre_aux_var = std::vector<int>(instance_data.global_data.upper_bound);
    for (int label = 0; label < instance_data.global_data.upper_bound; label++)
    {
        no_hole_incre_aux_var[label] = instance_data.vh->get_new_var();

        std::vector<int> node_vertices(instance_data.global_data.g->n);

        for (int vertex = 0; vertex < instance_data.global_data.g->n; vertex++)
        {
            node_vertices[vertex] = vertex * instance_data.global_data.upper_bound + label + 1;
            instance_data.cc->add_clause({no_hole_incre_aux_var[label], -node_vertices[vertex]});
        }

        node_vertices.push_back(-no_hole_incre_aux_var[label]);
        instance_data.cc->add_clause(node_vertices);
    }
    for (int i = 1; i < (int)no_hole_incre_aux_var.size(); i++)
    {
        instance_data.cc->add_clause({-no_hole_incre_aux_var[i], no_hole_incre_aux_var[i - 1]});
    }
}

void IncreNoHole::ignore_label(const IncreInstanceData &instance_data, int label)
{
    instance_data.cc->add_clause({-no_hole_incre_aux_var[label - 1]});
}