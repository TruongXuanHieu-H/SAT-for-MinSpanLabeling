#include "ite_amo_vertex.h"

#include <vector>
#include <cmath>

void IteAMOVertex::encode_vertices_constraint(const IteInstanceData &instance_data)
{
    for (int label = 0; label < instance_data.label; label++)
    {
        std::vector<int> node_vertices(instance_data.global_data.g->n);

        for (int vertex = 0; vertex < instance_data.global_data.g->n; vertex++)
        {
            node_vertices[vertex] = vertex * instance_data.label + label + 1;
        }

        encode_at_most_one_product(instance_data, node_vertices);
    }
}

void IteAMOVertex::encode_at_most_one_product(const IteInstanceData &instance_data, const std::vector<int> &vars)
{
    if (vars.size() < 2)
        return;
    if (vars.size() == 2)
    {
        instance_data.cc->add_clause({vars[0], vars[1]});
        instance_data.cc->add_clause({-1 * vars[0], -1 * vars[1]});
        return;
    }

    int len = vars.size();
    int p = std::ceil(std::sqrt(len));
    int q = std::ceil((float)len / (float)p);

    std::vector<int> u_vars;
    for (int i = 1; i <= p; ++i)
        u_vars.push_back(instance_data.vh->get_new_var());

    std::vector<int> v_vars;
    for (int j = 1; j <= q; ++j)
        v_vars.push_back(instance_data.vh->get_new_var());

    for (int idx = 0; idx < (int)vars.size(); ++idx)
    {
        instance_data.cc->add_clause({-1 * vars[idx], v_vars[std::floor(idx / p)]});
        instance_data.cc->add_clause({-1 * vars[idx], u_vars[idx % p]});
    }

    encode_amo_seq(instance_data, u_vars);
    encode_amo_seq(instance_data, v_vars);
};

void IteAMOVertex::encode_amo_seq(const IteInstanceData &instance_data, const std::vector<int> &vars)
{
    if (vars.size() < 2)
        return;

    int prev = vars[0];

    for (int idx = 1; idx < (int)vars.size() - 1; ++idx)
    {
        int curr = vars[idx];
        int next = instance_data.vh->get_new_var();
        instance_data.cc->add_clause({-1 * prev, -1 * curr});
        instance_data.cc->add_clause({-1 * prev, next});
        instance_data.cc->add_clause({-1 * curr, next});

        prev = next;
    }
    instance_data.cc->add_clause({-1 * prev, -1 * vars[vars.size() - 1]});
};