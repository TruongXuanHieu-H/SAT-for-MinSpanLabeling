#ifndef INCRE_INSTANCE_H
#define INCRE_INSTANCE_H

#include "incre_instance_data.h"
#include "../../global_data.h"
#include <limits>

class IncreInstance
{
public:
    IncreInstance(GlobalData &global_data);
    virtual ~IncreInstance();

    int encode_and_solve_problem();
    void encode_and_print_dimacs();

private:
    GlobalData &global_data;
    IncreInstanceData *instance_data;

    int recalculate_solution(const std::vector<int> &node_labels);
};

#endif