#include "ite_ladder_abp.h"

#include <assert.h>
#include <cmath>

void IteLadderABP::encode_target_value(const IteInstanceData &instance_data)
{
    std::vector<std::vector<int>> ladders_vars;
    for (int vertex = 0; vertex < instance_data.global_data.g->n; vertex++)
    {
        std::vector<int> ladder_vars;
        for (int label = 0; label < instance_data.label; label++)
        {
            ladder_vars.push_back(vertex * instance_data.label + label + 1);
        }
        ladders_vars.push_back(ladder_vars);
    }

    for (int i = 0; i < instance_data.global_data.g->n; i++)
    {
        encode_ladder(instance_data, ladders_vars[i], instance_data.global_data.target_value);
    }

    for (auto edge : instance_data.global_data.g->edges)
    {
        connect_ladder(instance_data, ladders_vars[edge.first - 1], ladders_vars[edge.second - 1], instance_data.global_data.target_value); // Have to reduce by 1 since edges are start from 1
    }
}

void IteLadderABP::encode_labels(const IteInstanceData &instance_data)
{
    for (int vertex = 0; vertex < instance_data.global_data.g->n; vertex++)
    {
        int number_windows = ceil((float)instance_data.label / instance_data.global_data.target_value);
        std::vector<std::vector<int>> vertice_vars(number_windows);

        for (int window = 0; window < number_windows; window++)
        {
            int start = vertex * instance_data.label + window * instance_data.global_data.target_value + 1;
            int end = std::min(
                vertex * instance_data.label + (window + 1) * instance_data.global_data.target_value,
                vertex * instance_data.label + instance_data.label);

            for (int var = start; var <= end; var++)
            {
                vertice_vars[window].push_back(var);
            }
        }

        std::vector<int> alo_clause = {};
        for (int window = 0; window < number_windows; window++)
        {
            int first_window_aux_var = get_target_value_aux_var(instance_data, vertice_vars[window], true);
            alo_clause.push_back(first_window_aux_var);
            for (int next_window = window + 1; next_window < number_windows; next_window++)
            {
                int second_window_aux_var = get_target_value_aux_var(instance_data, vertice_vars[next_window], true);
                instance_data.cc->add_clause({-first_window_aux_var, -second_window_aux_var});
            }
        }
        instance_data.cc->add_clause(alo_clause);
    }
}