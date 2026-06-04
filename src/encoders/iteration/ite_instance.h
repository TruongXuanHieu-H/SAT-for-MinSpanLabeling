#ifndef ITE_INSTANCE_H
#define ITE_INSTANCE_H

#include "ite_instance_data.h"

class IteInstance
{
public:
    IteInstance(int target_value, int label);
    virtual ~IteInstance();

    int encode_and_solve_problem();
    void encode_and_print_dimacs();

private:
    int SAT_res = 0;
    IteInstanceData *data;

    int recalculate_solution(const std::vector<int> &node_labels);
};

#endif