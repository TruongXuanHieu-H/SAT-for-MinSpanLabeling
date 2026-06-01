#ifndef ITERATIVE_MMSL_INSTANCE_H
#define ITERATIVE_MMSL_INSTANCE_H

class IterativeMMSLInstance
{
public:
    IterativeMMSLInstance(int width);
    virtual ~IterativeMMSLInstance();

    int encode_and_solve_problem();
    void encode_and_print_dimacs();

private:
    int SAT_res = 0;

    int verify_solution();
};

#endif