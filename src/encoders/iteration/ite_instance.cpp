#include "ite_instance.h"
#include "ite_encoder.h"
#include "../../global_data.h"
#include "../verifier/verifier.h"
#include "assert.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

IteInstance::IteInstance(GlobalData &global_data, int label)
{
    instance_data = std::make_unique<IteInstanceData>(global_data, label);
}

IteInstance::~IteInstance() {}

int IteInstance::encode_and_solve_problem()
{
    std::cout << "c " << instance_data->get_signature() << " Minimize Makespan Labeling problem (" << instance_data->global_data.g.graph_name << "):" << std::endl;

    instance_data->setup_for_solving();
    std::cout << "c " << instance_data->get_signature() << " Encoding starts with target value = " << instance_data->global_data.target_value << ":\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    instance_data->enc->encode_min_makespan_labeling();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    std::cout << "c " << instance_data->get_signature() << " Encoding duration: " << encode_duration << "ms" << ".\n";
    std::cout << "c " << instance_data->get_signature() << " Number of clauses: " << instance_data->cc->size() << ".\n";
    std::cout << "c " << instance_data->get_signature() << " Number of variables: " << instance_data->vh->size() << ".\n";

    t1 = std::chrono::high_resolution_clock::now();
    SAT_res = instance_data->solver->solve();
    t2 = std::chrono::high_resolution_clock::now();
    auto solving_duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "c " << instance_data->get_signature() << " Solving duration: " << solving_duration << " ms.\n";
    if (SAT_res == 10)
    {
        std::cout << "s " << instance_data->get_signature() << " SAT (w = " << instance_data->global_data.target_value << ").\n";

        std::vector<int> label_assignment = instance_data->solver->extract_result(instance_data->global_data.g.n, instance_data->label);

        std::cout << "c " << instance_data->get_signature() << "Label assignment: ";
        for (int l : label_assignment)
            std::cout << l << " ";
        std::cout << "\n";

        if (instance_data->global_data.enable_solution_verification)
        {
        }
    }
    else if (SAT_res == 20)
        std::cout << "s " << instance_data->get_signature() << " UNSAT (w = " << instance_data->global_data.target_value << ").\n";
    else
    {
        std::cout << "s " << instance_data->get_signature() << " Error at w = " << instance_data->global_data.target_value << ", SAT result: " << SAT_res << ".\n";
        return -20;
    }

    return SAT_res;
};

void IteInstance::encode_and_print_dimacs()
{
    std::cerr << "c " << instance_data->get_signature() << " DIMAC printing is not implemented.\n";
    exit(-1);
};