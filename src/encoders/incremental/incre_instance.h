#ifndef INCRE_INSTANCE_H
#define INCRE_INSTANCE_H

#include "incre_instance_data.h"
#include <limits>

class IncreInstance
{
public:
    IncreInstance(int target_value, int lower_bound, int upper_bound);
    virtual ~IncreInstance();

    int encode_and_solve_problem();
    void encode_and_print_dimacs();

private:
    IncreInstanceData *data;

    int recalculate_solution(const std::vector<int> &node_labels);
};

#endif