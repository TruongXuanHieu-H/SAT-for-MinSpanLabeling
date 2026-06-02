#ifndef INCRE_MMSL_INSTANCE_H
#define INCRE_MMSL_INSTANCE_H

#include <limits>

class IncreInstance
{
public:
    IncreInstance(int target_value, int lower_bound, int upper_bound);
    virtual ~IncreInstance();

    int encode_and_solve_problem();
    void encode_and_print_dimacs();

private:
    int verify_solution();
};

#endif