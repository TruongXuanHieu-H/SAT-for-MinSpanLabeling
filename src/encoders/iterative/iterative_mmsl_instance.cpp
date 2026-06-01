#include "iterative_mmsl_instance.h"
#include "iterative_instance_data.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"
#include <iostream>
#include <fstream>
#include <chrono>

IterativeMMSLInstance::IterativeMMSLInstance(int width)
{
    IterativeInstanceData::width = width;
}

IterativeMMSLInstance::~IterativeMMSLInstance() {};

/*
    Return the result of ABP:
    -   0 if graph only contains 1 vertex.
    -   10 if SAT (including w < 2 because it is always SAT).
    -   20 if UNSAT.
    -   -20 for undefined answers.
    -   -10 for incorrect SAT answers.
*/
int IterativeMMSLInstance::encode_and_solve_problem()
{
    std::cout << "c " << IterativeInstanceData::get_signature() << " Antibandwidth problem with w = " << IterativeInstanceData::width << " (" << GlobalData::g->graph_name << "):" << std::endl;
    if (GlobalData::g->n < 1)
    {
        std::cout << "c " << IterativeInstanceData::get_signature() << " The input graph is too small, there is nothing to encode here." << std::endl;
        SAT_res = 0; // should break loop
        return 0;
    }
    if (IterativeInstanceData::width < 2)
    {
        std::cout << "c " << IterativeInstanceData::get_signature() << " There is always at least 1 distance in any labelling. There is nothing to encode here." << std::endl;
        SAT_res = 10; // check solution can not be invoked
        return 10;
    }

    IterativeInstanceData::setup_for_solving();
    std::cout << "c " << IterativeInstanceData::get_signature() << " Encoding starts with w = " << IterativeInstanceData::width << ":" << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();
    IterativeInstanceData::enc->encode_antibandwidth();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "c " << IterativeInstanceData::get_signature() << " Encoding duration: " << encode_duration << "ms" << ".\n";
    std::cout << "c " << IterativeInstanceData::get_signature() << " Number of clauses: " << IterativeInstanceData::cc->size() << ".\n";
    std::cout << "c " << IterativeInstanceData::get_signature() << " Number of variables: " << IterativeInstanceData::vh->size() << ".\n";
    std::cout << "c " << IterativeInstanceData::get_signature() << " SAT Solving starts:" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    SAT_res = IterativeInstanceData::solver->solve();
    t2 = std::chrono::high_resolution_clock::now();
    auto solving_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "c " << IterativeInstanceData::get_signature() << " Solving duration: " << solving_duration << " ms.\n";
    std::cout << "c " << IterativeInstanceData::get_signature() << " Answer:\n";
    if (SAT_res == 10)
    {
        std::cout << "s " << IterativeInstanceData::get_signature() << " SAT (w = " << IterativeInstanceData::width << ").\n";
    }
    else if (SAT_res == 20)
        std::cout << "s " << IterativeInstanceData::get_signature() << " UNSAT (w = " << IterativeInstanceData::width << ").\n";
    else
    {
        std::cout << "s " << IterativeInstanceData::get_signature() << " Error at w = " << IterativeInstanceData::width << ", SAT result: " << SAT_res << ".\n";
        IterativeInstanceData::cleanup_solving();
        return -20;
    }

    if (GlobalData::enable_solution_verification && SAT_res == 10)
    {
        int solution_abp = verify_solution();
        if (solution_abp < IterativeInstanceData::width)
        {
            std::cerr << "c " << IterativeInstanceData::get_signature() << " Error, the solution is not correct, antibandwidth should be at least " << IterativeInstanceData::width << ", but it is " << solution_abp << ".\n";

            IterativeInstanceData::cleanup_solving();
            return -10;
        }
        else if (solution_abp == IterativeInstanceData::width)
        {
            std::cout << "c " + IterativeInstanceData::get_signature() + " The solution is correct.\n";
        }
        else
        {
            std::cout << "c " + IterativeInstanceData::get_signature() + " Found an optimal solution " << solution_abp << ".\n ";
        }
    }

    IterativeInstanceData::cleanup_solving();

    return SAT_res;
};

int IterativeMMSLInstance::verify_solution()
{
    std::vector<int> node_labels = IterativeInstanceData::solver->extract_result();
    if ((int)node_labels.size() == 0)
    {
        return 0;
    }
    int min_dist = GlobalData::g->calculate_antibandwidth(node_labels);

    std::cout << "c " << IterativeInstanceData::get_signature() << " Solution check w = " << min_dist << ".\n";

    return min_dist;
}

void IterativeMMSLInstance::encode_and_print_dimacs()
{
    std::cout << "c " + IterativeInstanceData::get_signature() + " Cyclic Antibandwidth problem with w = " << IterativeInstanceData::width << " (" << GlobalData::g->graph_name << "):\n";
    if (GlobalData::g->n < 1)
    {
        std::cout << "c " + IterativeInstanceData::get_signature() + " The input graph is too small, there is nothing to encode here.\n";
        return;
    }
    if (IterativeInstanceData::width < 2)
    {
        std::cout << "c " + IterativeInstanceData::get_signature() + " There is always at least 1 distance in any labelling. There is nothing to encode here.\n";
        return;
    }

    IterativeInstanceData::setup_for_encoding();
    std::cout << "c " + IterativeInstanceData::get_signature() + " Encoding starts with w = " << IterativeInstanceData::width << ":\n";

    IterativeInstanceData::enc->encode_antibandwidth();
    std::cout << "c " + IterativeInstanceData::get_signature() + " Number of clauses: " << IterativeInstanceData::cc->size() << ".\n";
    std::cout << "c " + IterativeInstanceData::get_signature() + " Number of variables: " << IterativeInstanceData::vh->size() << ".\n";

    std::string file_name = "abp-" + GlobalData::g->graph_name + "-k" + std::to_string(IterativeInstanceData::width) + ".cnf";
    std::ofstream out(GlobalData::dimacs_directory + "/" + file_name);
    if (!out.is_open())
    {
        std::cerr << "c " + IterativeInstanceData::get_signature() + " Error: cannot open file " << GlobalData::dimacs_directory + file_name << " for writing.\n";
        IterativeInstanceData::cleanup_encoding();
        return;
    }
    IterativeInstanceData::export_dimacs(out);
    out.close();

    IterativeInstanceData::cleanup_encoding();
};