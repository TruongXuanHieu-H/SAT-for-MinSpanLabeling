#include "ite_ladder.h"
#include "ite_instance_data.h"
#include "../../global_data.h"
#include <iostream>
#include <numeric>
#include <algorithm>
#include <assert.h>
#include <cmath>

IteLadder::IteLadder(IteInstanceData &instance_data) : IteEncoder(instance_data) {}
IteLadder::~IteLadder() {}

void IteLadder::encode_antibandwidth()
{
    do_encode_antibandwidth();
}

void IteLadder::do_encode_antibandwidth()
{
    assert(obj_k_aux_vars.size() == 0);

    encode_symmetry_break();

    encode_vertices();

    encode_obj_k();

    encode_labels();
};

void IteLadder::encode_vertices()
{
    for (int label = 0; label < instance_data.label; label++)
    {
        std::vector<int> node_vertices_eo(instance_data.global_data.g->n);

        for (int vertex = 0; vertex < instance_data.global_data.g->n; vertex++)
        {
            node_vertices_eo[vertex] = vertex * instance_data.label + label + 1;
        }

        switch (instance_data.global_data.vertices_mode)
        {
        case VerticesMode::no_hole:
            encode_at_least_one_naive(node_vertices_eo);
            break;
        case VerticesMode::has_hole:
            encode_at_most_one_product(node_vertices_eo);
            break;

        default:
            break;
        }
    }
}

void IteLadder::encode_at_least_one_naive(const std::vector<int> &vars)
{
    instance_data.cc->add_clause(vars);
}

void IteLadder::encode_at_most_one_product(const std::vector<int> &vars)
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

    encode_amo_seq(u_vars);
    encode_amo_seq(v_vars);
};

void IteLadder::encode_amo_seq(const std::vector<int> &vars)
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

int IteLadder::get_obj_k_aux_var(std::vector<int> key, bool is_key_exist)
{
    if (key.front() == key.back() && key.size() == 1)
    {
        return key.front();
    }

    auto pair = obj_k_aux_vars.find(key);

    if (is_key_exist)
    {
        assert(pair != obj_k_aux_vars.end());
    }

    if (pair != obj_k_aux_vars.end())
    {
        return pair->second;
    }

    int new_obj_k_aux_var = instance_data.vh->get_new_var();
    obj_k_aux_vars.insert({key, new_obj_k_aux_var});
    return new_obj_k_aux_var;
}

void IteLadder::encode_labels()
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
            int first_window_aux_var = get_obj_k_aux_var(vertice_vars[window], true);
            alo_clause.push_back(first_window_aux_var);
            for (int next_window = window + 1; next_window < number_windows; next_window++)
            {
                int second_window_aux_var = get_obj_k_aux_var(vertice_vars[next_window], true);
                instance_data.cc->add_clause({-first_window_aux_var, -second_window_aux_var});
            }
        }
        instance_data.cc->add_clause(alo_clause);
    }
}

void IteLadder::encode_obj_k()
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
        encode_ladder(ladders_vars[i], instance_data.global_data.target_value);
    }

    for (auto edge : instance_data.global_data.g->edges)
    {
        connect_ladder(ladders_vars[edge.first - 1], ladders_vars[edge.second - 1], instance_data.global_data.target_value); // Have to reduce by 1 since edges are start from 1
    }
}

void IteLadder::encode_ladder(const std::vector<int> ladder_vars, int width)
{
    if (instance_data.global_data.verbose)
    {
        std::cout << "c Encoding ladder ";
        for (int var : ladder_vars)
        {
            std::cout << var << " ";
        }
        std::cout << "with width " << width << std::endl;
    }

    std::vector<std::vector<int>> windows_vars;
    int number_ladder_vars = (int)ladder_vars.size();

    for (int i = 0; i < number_ladder_vars; i += width)
    {
        int end = std::min(i + width, number_ladder_vars);
        windows_vars.emplace_back(ladder_vars.begin() + i, ladder_vars.begin() + end);
    }

    int number_windows = (int)windows_vars.size();

    for (int i = 0; i < number_windows; i++)
    {
        encode_window(windows_vars[i], i == 0, i == number_windows - 1);
    }

    for (int i = 0; i < number_windows - 1; i++)
    {
        connect_windows(windows_vars[i], windows_vars[i + 1]);
    }
}

void IteLadder::encode_window(const std::vector<int> window_vars, bool is_first_window, bool is_last_window)
{
    if (instance_data.global_data.verbose)
    {
        std::cout << "c Encoding window ";
        for (int var : window_vars)
        {
            std::cout << var << " ";
        }
        std::cout << std::endl;
    }

    int window_vars_size = (int)window_vars.size();

    if (!is_first_window)
    {
        for (int i = 1; i < window_vars_size; i++)
        {
            instance_data.cc->add_clause({-(window_vars[i]),
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i + 1))});
        }

        for (int i = 0; i < window_vars_size - 1; i++)
        {
            instance_data.cc->add_clause({-get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i + 1)),
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i + 2))});
        }

        for (int i = window_vars_size - 1; i > 0; i--)
        {
            instance_data.cc->add_clause({window_vars[i],
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i)),
                                          -get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i + 1))});
        }

        for (int i = window_vars_size - 1; i > 0; i--)
        {
            instance_data.cc->add_clause({-(window_vars[i]),
                                          -get_obj_k_aux_var(std::vector<int>(window_vars.begin(), window_vars.begin() + i))});
        }
    }

    if (!is_last_window)
    {
        for (int i = window_vars_size - 2; i >= 0; i--)
        {
            instance_data.cc->add_clause({-(window_vars[i]),
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i, window_vars.end()))});
        }

        for (int i = window_vars_size - 1; i >= 1; i--)
        {
            instance_data.cc->add_clause({-get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i, window_vars.end())),
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i - 1, window_vars.end()))});
        }

        for (int i = 0; i < window_vars_size - 1; i++)
        {
            instance_data.cc->add_clause({window_vars[i],
                                          get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i + 1, window_vars.end())),
                                          -get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i, window_vars.end()))});
        }

        if (is_first_window)
        {
            for (int i = 0; i < window_vars_size - 1; i++)
            {
                instance_data.cc->add_clause({-(window_vars[i]),
                                              -get_obj_k_aux_var(std::vector<int>(window_vars.begin() + i + 1, window_vars.end()))});
            }
        }
    }
}

void IteLadder::connect_windows(const std::vector<int> first_window_vars, const std::vector<int> second_window_vars)
{
    if (instance_data.global_data.verbose)
    {
        std::cout << "c Connecting windows: " << std::endl;
        std::cout << "c First window vars: ";
        for (int var : first_window_vars)
        {
            std::cout << var << " ";
        }
        std::cout << std::endl;
        std::cout << "c Second window vars: ";
        for (int var : second_window_vars)
        {
            std::cout << var << " ";
        }
        std::cout << std::endl;
    }

    int number_first_window_vars = (int)first_window_vars.size();
    int number_second_window_vars = (int)second_window_vars.size();
    assert(number_first_window_vars >= number_second_window_vars);

    int number_connections = number_first_window_vars == number_second_window_vars ? number_second_window_vars - 1 : number_second_window_vars;

    for (int i = 0; i < number_connections; i++)
    {
        instance_data.cc->add_clause({-get_obj_k_aux_var(std::vector<int>(first_window_vars.begin() + i + 1, first_window_vars.end())),
                                      -get_obj_k_aux_var(std::vector<int>(second_window_vars.begin(), second_window_vars.begin() + i + 1))});
    }
}

void IteLadder::connect_ladder(const std::vector<int> first_ladder_vars, const std::vector<int> second_ladder_vars, int width)
{
    if (instance_data.global_data.verbose)
    {
        std::cout << "c Connecting ladders: " << std::endl;
        std::cout << "c First ladder vars: ";
        for (int var : first_ladder_vars)
        {
            std::cout << var << " ";
        }
        std::cout << std::endl;
        std::cout << "c Second ladder vars: ";
        for (int var : second_ladder_vars)
        {
            std::cout << var << " ";
        }
        std::cout << std::endl;
    }

    assert(first_ladder_vars.size() == second_ladder_vars.size());

    int number_connections = first_ladder_vars.size() - width + 1;
    for (int i = 0; i < number_connections; i++)
    {
        int mod = i % width;
        if (mod == 0)
        {
            int first_aux_var = get_obj_k_aux_var(std::vector<int>(first_ladder_vars.begin() + i, first_ladder_vars.begin() + i + width));
            int second_aux_var = get_obj_k_aux_var(std::vector<int>(second_ladder_vars.begin() + i, second_ladder_vars.begin() + i + width));

            instance_data.cc->add_clause({-first_aux_var, -second_aux_var});
        }
        else
        {
            int first_aux_var_1 = get_obj_k_aux_var(std::vector<int>(first_ladder_vars.begin() + i, first_ladder_vars.begin() + i + width - mod));
            int first_aux_var_2 = get_obj_k_aux_var(std::vector<int>(first_ladder_vars.begin() + i + width - mod, first_ladder_vars.begin() + i + width));
            int second_aux_var_1 = get_obj_k_aux_var(std::vector<int>(second_ladder_vars.begin() + i, second_ladder_vars.begin() + i + width - mod));
            int second_aux_var_2 = get_obj_k_aux_var(std::vector<int>(second_ladder_vars.begin() + i + width - mod, second_ladder_vars.begin() + i + width));

            instance_data.cc->add_clause({-first_aux_var_1, -second_aux_var_1});
            instance_data.cc->add_clause({-first_aux_var_1, -second_aux_var_2});
            instance_data.cc->add_clause({-first_aux_var_2, -second_aux_var_1});
            instance_data.cc->add_clause({-first_aux_var_2, -second_aux_var_2});
        }
    }
}
