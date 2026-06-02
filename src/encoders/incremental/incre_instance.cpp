#include "incre_instance.h"
#include "incre_instance_data.h"
#include "../../global_data.h"
#include <iostream>
#include <fstream>
#include <chrono>

IncreInstance::IncreInstance(int target_value, int lower_bound, int upper_bound)
{
    IncreInstanceData::target_value = target_value;
    IncreInstanceData::lower_bound = lower_bound;
    IncreInstanceData::upper_bound = upper_bound;
};

int IncreInstance::encode_and_solve_problem()
{
    std::cout << "c Minimize Makespan Labeling Antibandwidth problem (" << GlobalData::g->graph_name << "):" << std::endl;
    if (GlobalData::g->n < 1)
    {
        std::cout << "c The input graph is too small, there is nothing to encode here." << std::endl;
        return 0;
    }

    IncreInstanceData::setup_for_solving();
    std::cout << "c Encoding starts with target value = " << IncreInstanceData::target_value << ":\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    IncreInstanceData::enc->encode_antibandwidth();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "c " << IncreInstanceData::get_signature() << " Encoding duration: " << encode_duration << "ms" << ".\n";
    std::cout << "c " << IncreInstanceData::get_signature() << " Number of clauses: " << IncreInstanceData::cc->size() << ".\n";
    std::cout << "c " << IncreInstanceData::get_signature() << " Number of variables: " << IncreInstanceData::vh->size() << ".\n";
    std::cout << "c " << IncreInstanceData::get_signature() << " SAT Solving starts:" << std::endl;

    for (int i = IncreInstanceData::upper_bound; i >= IncreInstanceData::lower_bound; i--)
    {
        t1 = std::chrono::high_resolution_clock::now();
        int SAT_res = IncreInstanceData::solver->solve();
        t2 = std::chrono::high_resolution_clock::now();
        auto solving_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        std::cout << "c " << IncreInstanceData::get_signature() << " Solving duration: " << solving_duration << " ms.\n";
        std::cout << "c " << IncreInstanceData::get_signature() << " Answer:\n";

        if (SAT_res == 10)
        {
            std::cout << "s " << IncreInstanceData::get_signature() << " SAT (label = " << i << ").\n";
        }
        else if (SAT_res == 20)
        {
            std::cout << "s " << IncreInstanceData::get_signature() << " UNSAT (label = " << i << ").\n";
            break;
        }
        else
        {
            std::cout << "s " << IncreInstanceData::get_signature() << " Error at label = " << i << ", SAT result: " << SAT_res << ".\n";
            IncreInstanceData::cleanup_solving();
            return -20;
        }

        if (GlobalData::enable_solution_verification && SAT_res == 10)
        {
            int solution_abp = verify_solution();
            if (solution_abp < IncreInstanceData::target_value)
            {
                std::cerr << "c " << IncreInstanceData::get_signature() << " Error, the solution is not correct, antibandwidth should be at least " << IncreInstanceData::target_value << ", but it is " << solution_abp << ".\n";

                IncreInstanceData::cleanup_solving();
                return -10;
            }
            else if (solution_abp == IncreInstanceData::target_value)
            {
                std::cout << "c " + IncreInstanceData::get_signature() + " The solution is correct.\n";
            }
            else
            {
                std::cout << "c " + IncreInstanceData::get_signature() + " Found an optimal solution " << solution_abp << ".\n ";
            }
        }

        IncreInstanceData::solver->add_clause
    }
};