#ifndef ITE_INSTANCE_H
#define ITE_INSTANCE_H

class IteInstance
{
public:
    IteInstance(int width);
    virtual ~IteInstance();

    int encode_and_solve_problem();
    void encode_and_print_dimacs();

private:
    int SAT_res = 0;

    int verify_solution();
};

#endif