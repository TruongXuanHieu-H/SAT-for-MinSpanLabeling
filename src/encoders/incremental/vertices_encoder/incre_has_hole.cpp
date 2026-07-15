#include "incre_has_hole.h"

#include <vector>

void IncreHasHole::encode_vertices_constraint(const IncreInstanceData &instance_data)
{
    // Nothing to encode here
    (void)instance_data;
}

void IncreHasHole::ignore_label(const IncreInstanceData &instance_data, int label)
{
    for (int j = 0; j < instance_data.global_data.g->n; j++)
    {
        instance_data.cc->add_clause({-(j * instance_data.global_data.upper_bound + label)});
    }
}