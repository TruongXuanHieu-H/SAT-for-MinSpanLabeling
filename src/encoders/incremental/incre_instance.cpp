#include "incre_instance.h"
#include "incre_encoder.h"
#include "../../global_data.h"
#include <iostream>
#include <fstream>
#include <chrono>

IncreInstance::IncreInstance(int target_value, int lower_bound, int upper_bound)
{
    data = new IncreInstanceData(target_value, lower_bound, upper_bound);
};

IncreInstance::~IncreInstance()
{
    delete data;
};

int IncreInstance::encode_and_solve_problem()
{
    std::cout << "c Minimize Makespan Labeling Antibandwidth problem (" << GlobalData::g->graph_name << "):" << std::endl;
    if (GlobalData::g->n < 1)
    {
        std::cout << "c The input graph is too small, there is nothing to encode here." << std::endl;
        return 0;
    }

    data->setup_for_solving();
    std::cout << "c Encoding starts with target value = " << data->target_value << ":\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    data->enc->encode_antibandwidth();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "c " << data->get_signature() << " Encoding duration: " << encode_duration << "ms" << ".\n";
    std::cout << "c " << data->get_signature() << " Number of clauses: " << data->cc->size() << ".\n";
    std::cout << "c " << data->get_signature() << " Number of variables: " << data->vh->size() << ".\n";
    std::cout << "c " << data->get_signature() << " SAT Solving starts:" << std::endl;

    for (int i = data->upper_bound; i >= data->lower_bound; i--)
    {
        t1 = std::chrono::high_resolution_clock::now();
        int SAT_res = data->solver->solve();
        t2 = std::chrono::high_resolution_clock::now();
        auto solving_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "c " << data->get_signature() << " Solving duration: " << solving_duration << " ms.\n";
        std::cout << "c " << data->get_signature() << " Answer:\n";

        if (SAT_res == 10)
        {
            std::cout << "s " << data->get_signature() << " SAT (label = " << i << ").\n";
        }
        else if (SAT_res == 20)
        {
            std::cout << "s " << data->get_signature() << " UNSAT (label = " << i << ").\n";
            break;
        }
        else
        {
            std::cout << "s " << data->get_signature() << " Error at label = " << i << ", SAT result: " << SAT_res << ".\n";
            data->cleanup_solving();
            return -20;
        }

        if (GlobalData::enable_solution_verification && SAT_res == 10)
        {
            int solution_abp = verify_solution();
            if (solution_abp < data->target_value)
            {
                std::cerr << "c " << data->get_signature() << " Error, the solution is not correct, antibandwidth should be at least " << data->target_value << ", but it is " << solution_abp << ".\n";

                data->cleanup_solving();
                return -10;
            }
            else if (solution_abp == data->target_value)
            {
                std::cout << "c " + data->get_signature() + " The solution is correct.\n";
            }
            else
            {
                std::cout << "c " + data->get_signature() + " Found an optimal solution " << solution_abp << ".\n ";
            }
        }

        for (int j = 0; j < GlobalData::g->n; j++)
        {
            data->solver->add_clause({-(j * GlobalData::g->n + i)});
        }
    }

    data->cleanup_solving();

    return 0;
};

int IncreInstance::verify_solution()
{
    std::vector<int> node_labels = data->solver->extract_result();
    if ((int)node_labels.size() == 0)
    {
        return 0;
    }
    int min_dist = GlobalData::g->calculate_antibandwidth(node_labels);

    std::cout << "c " << data->get_signature() << " Solution check w = " << min_dist << ".\n";

    return min_dist;
}

void IncreInstance::encode_and_print_dimacs()
{
    std::cout << "c " + data->get_signature() + " Antibandwidth problem with w = " << data->target_value << " (" << GlobalData::g->graph_name << "):\n";

    data->setup_for_encoding();
    std::cout << "c " + data->get_signature() + " Encoding starts with w = " << data->target_value << ":\n";

    data->enc->encode_antibandwidth();
    std::cout << "c " + data->get_signature() + " Number of clauses: " << data->cc->size() << ".\n";
    std::cout << "c " + data->get_signature() + " Number of variables: " << data->vh->size() << ".\n";

    std::string file_name = "abp-" + GlobalData::g->graph_name + "-k" + std::to_string(data->target_value) + ".cnf";
    std::ofstream out(GlobalData::dimacs_directory + "/" + file_name);
    if (!out.is_open())
    {
        std::cerr << "c " + data->get_signature() + " Error: cannot open file " << GlobalData::dimacs_directory + file_name << " for writing.\n";
        data->cleanup_encoding();
        return;
    }
    data->export_dimacs(out);
    out.close();

    data->cleanup_encoding();
};