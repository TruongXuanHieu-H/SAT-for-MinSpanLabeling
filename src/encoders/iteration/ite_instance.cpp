#include "ite_instance.h"
#include "ite_instance_data.h"
#include "ite_ladder.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"
#include <iostream>
#include <fstream>
#include <chrono>

IteInstance::IteInstance(GlobalData &global_data, int label) : global_data(global_data)
{
    data = std::make_unique<IteInstanceData>(global_data, label);
}

IteInstance::~IteInstance() {}

int IteInstance::encode_and_solve_problem()
{
    data->setup_for_solving();

    auto t1 = std::chrono::high_resolution_clock::now();
    data->enc->encode_antibandwidth();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "c " << data->get_signature() << " Encoding duration: " << encode_duration << "ms" << ".\n";
    std::cout << "c " << data->get_signature() << " Number of clauses: " << data->cc->size() << ".\n";
    std::cout << "c " << data->get_signature() << " Number of variables: " << data->vh->size() << ".\n";

    t1 = std::chrono::high_resolution_clock::now();
    SAT_res = data->solver->solve();
    t2 = std::chrono::high_resolution_clock::now();
    auto solving_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "c " << data->get_signature() << " Solving duration: " << solving_duration << " ms.\n";
    if (SAT_res == 10)
    {
        std::cout << "s " << data->get_signature() << " SAT (w = " << global_data.target_value << ").\n";

        std::vector<int> label_assignment = data->solver->extract_result(global_data.g->n, data->label);

        std::cout << "Label assignment: ";
        for (int l : label_assignment)
            std::cout << l << " ";
        std::cout << "\n";

        if (global_data.enable_solution_verification)
        {
            int solution_abp = recalculate_solution(label_assignment);
            if (solution_abp < global_data.target_value)
            {
                std::cerr << "c " << data->get_signature() << " Error, the solution is not correct, target value should be at least " << global_data.target_value << ", but it is " << solution_abp << ".\n";
                return -10;
            }
        }
    }
    else if (SAT_res == 20)
        std::cout << "s " << data->get_signature() << " UNSAT (w = " << global_data.target_value << ").\n";
    else
    {
        std::cout << "s " << data->get_signature() << " Error at w = " << global_data.target_value << ", SAT result: " << SAT_res << ".\n";
        return -20;
    }

    return SAT_res;
};

int IteInstance::recalculate_solution(const std::vector<int> &node_labels)
{
    if ((int)node_labels.size() == 0)
    {
        return 0;
    }
    int min_dist = global_data.g->calculate_antibandwidth(node_labels);

    return min_dist;
}

void IteInstance::encode_and_print_dimacs()
{
    std::cout << "c " + data->get_signature() + " Cyclic Antibandwidth problem with w = " << global_data.target_value << " (" << global_data.g->graph_name << "):\n";
    if (global_data.g->n < 1)
    {
        std::cout << "c " + data->get_signature() + " The input graph is too small, there is nothing to encode here.\n";
        return;
    }
    if (global_data.target_value < 2)
    {
        std::cout << "c " + data->get_signature() + " There is always at least 1 distance in any labelling. There is nothing to encode here.\n";
        return;
    }

    data->setup_for_encoding();
    std::cout << "c " + data->get_signature() + " Encoding starts with w = " << global_data.target_value << ":\n";

    data->enc->encode_antibandwidth();
    std::cout << "c " + data->get_signature() + " Number of clauses: " << data->cc->size() << ".\n";
    std::cout << "c " + data->get_signature() + " Number of variables: " << data->vh->size() << ".\n";

    std::string file_name = "abp-" + global_data.g->graph_name + "-k" + std::to_string(global_data.target_value) + ".cnf";
    std::ofstream out(global_data.dimacs_directory + "/" + file_name);
    if (!out.is_open())
    {
        std::cerr << "c " + data->get_signature() + " Error: cannot open file " << global_data.dimacs_directory + file_name << " for writing.\n";
        return;
    }
    data->export_dimacs(out);
    out.close();
};