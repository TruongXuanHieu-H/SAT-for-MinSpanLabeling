#include "ite_instance.h"
#include "ite_instance_data.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"
#include <iostream>
#include <fstream>
#include <chrono>

IteInstance::IteInstance(int width)
{
    IteInstanceData::width = width;
}

IteInstance::~IteInstance() {};

/*
    Return the result of ABP:
    -   0 if graph only contains 1 vertex.
    -   10 if SAT (including w < 2 because it is always SAT).
    -   20 if UNSAT.
    -   -20 for undefined answers.
    -   -10 for incorrect SAT answers.
*/
int IteInstance::encode_and_solve_problem()
{
    std::cout << "c " << IteInstanceData::get_signature() << " Antibandwidth problem with w = " << IteInstanceData::width << " (" << GlobalData::g->graph_name << "):" << std::endl;
    if (GlobalData::g->n < 1)
    {
        std::cout << "c " << IteInstanceData::get_signature() << " The input graph is too small, there is nothing to encode here." << std::endl;
        SAT_res = 0; // should break loop
        return 0;
    }
    if (IteInstanceData::width < 2)
    {
        std::cout << "c " << IteInstanceData::get_signature() << " There is always at least 1 distance in any labelling. There is nothing to encode here." << std::endl;
        SAT_res = 10; // check solution can not be invoked
        return 10;
    }

    IteInstanceData::setup_for_solving();
    std::cout << "c " << IteInstanceData::get_signature() << " Encoding starts with w = " << IteInstanceData::width << ":" << std::endl;

    auto t1 = std::chrono::high_resolution_clock::now();
    IteInstanceData::enc->encode_antibandwidth();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "c " << IteInstanceData::get_signature() << " Encoding duration: " << encode_duration << "ms" << ".\n";
    std::cout << "c " << IteInstanceData::get_signature() << " Number of clauses: " << IteInstanceData::cc->size() << ".\n";
    std::cout << "c " << IteInstanceData::get_signature() << " Number of variables: " << IteInstanceData::vh->size() << ".\n";
    std::cout << "c " << IteInstanceData::get_signature() << " SAT Solving starts:" << std::endl;

    t1 = std::chrono::high_resolution_clock::now();
    SAT_res = IteInstanceData::solver->solve();
    t2 = std::chrono::high_resolution_clock::now();
    auto solving_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "c " << IteInstanceData::get_signature() << " Solving duration: " << solving_duration << " ms.\n";
    std::cout << "c " << IteInstanceData::get_signature() << " Answer:\n";
    if (SAT_res == 10)
    {
        std::cout << "s " << IteInstanceData::get_signature() << " SAT (w = " << IteInstanceData::width << ").\n";
    }
    else if (SAT_res == 20)
        std::cout << "s " << IteInstanceData::get_signature() << " UNSAT (w = " << IteInstanceData::width << ").\n";
    else
    {
        std::cout << "s " << IteInstanceData::get_signature() << " Error at w = " << IteInstanceData::width << ", SAT result: " << SAT_res << ".\n";
        IteInstanceData::cleanup_solving();
        return -20;
    }

    if (GlobalData::enable_solution_verification && SAT_res == 10)
    {
        int solution_abp = verify_solution();
        if (solution_abp < IteInstanceData::width)
        {
            std::cerr << "c " << IteInstanceData::get_signature() << " Error, the solution is not correct, antibandwidth should be at least " << IteInstanceData::width << ", but it is " << solution_abp << ".\n";

            IteInstanceData::cleanup_solving();
            return -10;
        }
        else if (solution_abp == IteInstanceData::width)
        {
            std::cout << "c " + IteInstanceData::get_signature() + " The solution is correct.\n";
        }
        else
        {
            std::cout << "c " + IteInstanceData::get_signature() + " Found an optimal solution " << solution_abp << ".\n ";
        }
    }

    IteInstanceData::cleanup_solving();

    return SAT_res;
};

int IteInstance::verify_solution()
{
    std::vector<int> node_labels = IteInstanceData::solver->extract_result();
    if ((int)node_labels.size() == 0)
    {
        return 0;
    }
    int min_dist = GlobalData::g->calculate_antibandwidth(node_labels);

    std::cout << "c " << IteInstanceData::get_signature() << " Solution check w = " << min_dist << ".\n";

    return min_dist;
}

void IteInstance::encode_and_print_dimacs()
{
    std::cout << "c " + IteInstanceData::get_signature() + " Cyclic Antibandwidth problem with w = " << IteInstanceData::width << " (" << GlobalData::g->graph_name << "):\n";
    if (GlobalData::g->n < 1)
    {
        std::cout << "c " + IteInstanceData::get_signature() + " The input graph is too small, there is nothing to encode here.\n";
        return;
    }
    if (IteInstanceData::width < 2)
    {
        std::cout << "c " + IteInstanceData::get_signature() + " There is always at least 1 distance in any labelling. There is nothing to encode here.\n";
        return;
    }

    IteInstanceData::setup_for_encoding();
    std::cout << "c " + IteInstanceData::get_signature() + " Encoding starts with w = " << IteInstanceData::width << ":\n";

    IteInstanceData::enc->encode_antibandwidth();
    std::cout << "c " + IteInstanceData::get_signature() + " Number of clauses: " << IteInstanceData::cc->size() << ".\n";
    std::cout << "c " + IteInstanceData::get_signature() + " Number of variables: " << IteInstanceData::vh->size() << ".\n";

    std::string file_name = "abp-" + GlobalData::g->graph_name + "-k" + std::to_string(IteInstanceData::width) + ".cnf";
    std::ofstream out(GlobalData::dimacs_directory + "/" + file_name);
    if (!out.is_open())
    {
        std::cerr << "c " + IteInstanceData::get_signature() + " Error: cannot open file " << GlobalData::dimacs_directory + file_name << " for writing.\n";
        IteInstanceData::cleanup_encoding();
        return;
    }
    IteInstanceData::export_dimacs(out);
    out.close();

    IteInstanceData::cleanup_encoding();
};