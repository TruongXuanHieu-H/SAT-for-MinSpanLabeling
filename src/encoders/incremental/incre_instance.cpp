#include "incre_instance.h"
#include "incre_encoder.h"
#include "../../global_data.h"
#include "assert.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

IncreInstance::IncreInstance(GlobalData &global_data) : global_data(global_data)
{
    instance_data = new IncreInstanceData(global_data);
};

IncreInstance::~IncreInstance()
{
    delete instance_data;
    instance_data = nullptr;
};

int IncreInstance::encode_and_solve_problem()
{
    std::cout << "c " << instance_data->get_signature() << " Minimize Makespan Labeling Antibandwidth problem (" << global_data.g->graph_name << "):" << std::endl;

    instance_data->setup_for_solving();
    std::cout << "c " << instance_data->get_signature() << " Encoding starts with target value = " << global_data.target_value << ":\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    instance_data->enc->encode_min_makespan_labeling();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "c " << instance_data->get_signature() << " Encoding duration: " << encode_duration << "ms" << ".\n";
    std::cout << "c " << instance_data->get_signature() << " Number of clauses: " << instance_data->cc->size() << ".\n";
    std::cout << "c " << instance_data->get_signature() << " Number of variables: " << instance_data->vh->size() << ".\n";

    for (int i = global_data.upper_bound; i >= global_data.lower_bound; i--)
    {
        std::cout << "c " << instance_data->get_signature() << " Solving for max label = " << i << ":\n";
        t1 = std::chrono::high_resolution_clock::now();
        int SAT_res = instance_data->solver->solve();
        t2 = std::chrono::high_resolution_clock::now();
        auto solving_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "c " << instance_data->get_signature() << " Solving duration: " << solving_duration << " ms.\n";

        if (SAT_res == 10)
        {
            std::cout << "s " << instance_data->get_signature() << " SAT (label = " << i << ").\n";

            std::vector<int> label_assignment = instance_data->solver->extract_result(global_data.g->n, global_data.upper_bound);

            std::cout << "Label assignment: ";
            for (int l : label_assignment)
                std::cout << l << " ";
            std::cout << "\n";

            if (global_data.enable_solution_verification)
            {
                int solution_abp = recalculate_solution(label_assignment);
                if (solution_abp < global_data.target_value)
                {
                    std::cerr << "c " << instance_data->get_signature() << " Error, the solution is not correct, antibandwidth should be at least " << global_data.target_value << ", but it is " << solution_abp << ".\n";

                    instance_data->cleanup_solving();
                    return -10;
                }
            }

            int max_used_label = *std::max_element(label_assignment.begin(), label_assignment.end());
            assert(max_used_label <= i);
            std::cout << "c " << instance_data->get_signature() << " Max used label: " << max_used_label << ".\n";

            for (int k = i; k >= max_used_label; k--)
            {
                instance_data->enc->ignore_label(k);
                std::cout << "c " << instance_data->get_signature() << " Label " << k << " is removed from searching.\n";
            }
            i = max_used_label;
        }
        else if (SAT_res == 20)
        {
            std::cout << "s " << instance_data->get_signature() << " UNSAT (label = " << i << ").\n";
            break;
        }
        else
        {
            std::cout << "s " << instance_data->get_signature() << " Error at label = " << i << ", SAT result: " << SAT_res << ".\n";
            instance_data->cleanup_solving();
            return -20;
        }
    }

    instance_data->cleanup_solving();

    return 0;
};

int IncreInstance::recalculate_solution(const std::vector<int> &node_labels)
{
    if ((int)node_labels.size() == 0)
    {
        return 0;
    }
    int min_dist = global_data.g->calculate_antibandwidth(node_labels);

    return min_dist;
}

void IncreInstance::encode_and_print_dimacs()
{
    instance_data->setup_for_encoding();

    instance_data->enc->encode_min_makespan_labeling();

    std::cout << "c " + instance_data->get_signature() + " Number of clauses: " << instance_data->cc->size() << ".\n";
    std::cout << "c " + instance_data->get_signature() + " Number of variables: " << instance_data->vh->size() << ".\n";

    std::string file_name = "abp-" + global_data.g->graph_name + "-k" + std::to_string(global_data.target_value) + ".cnf";
    std::ofstream out(global_data.dimacs_directory + "/" + file_name);
    if (!out.is_open())
    {
        std::cerr << "c " + instance_data->get_signature() + " Error: cannot open file " << global_data.dimacs_directory + file_name << " for writing.\n";
        instance_data->cleanup_encoding();
        return;
    }
    instance_data->export_dimacs(out);
    out.close();

    instance_data->cleanup_encoding();
};