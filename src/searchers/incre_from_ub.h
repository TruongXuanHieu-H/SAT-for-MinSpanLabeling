#ifndef INCRE_FROM_UB_H
#define INCRE_FROM_UB_H

#include "searcher.h"

class IncreFromUB : public Searcher
{
public:
    IncreFromUB(int target_value, int lower_bound, int upper_bound);
    ~IncreFromUB();

    void encode_and_solve() override;
    void encode_and_print_dimacs() override;

protected:
    pid_t work_pid;

    void create_work_pid();
};
#endif