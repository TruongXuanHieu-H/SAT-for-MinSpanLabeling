#ifndef MMSL_INCREMENTAL_FROM_UB_H
#define MMSL_INCREMENTAL_FROM_UB_H

#include "mmsl_searcher.h"

class MMSLIncrementalFromUB : MMSLSearcher
{
public:
    MMSLIncrementalFromUB();
    ~MMSLIncrementalFromUB();

    void encode_and_solve() override;
    void encode_and_print_dimacs() override;

protected:
    pid_t work_pid;

    void create_work_pid();
};
#endif