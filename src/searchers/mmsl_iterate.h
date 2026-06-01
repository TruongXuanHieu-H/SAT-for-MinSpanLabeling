#ifndef MMSL_ITERATE_H
#define MMSL_ITERATE_H

#include "mmsl_searcher.h"

class MMSLIterate : public MMSLSearcher
{
public:
    MMSLIterate();
    ~MMSLIterate();

    void encode_and_solve() override;
    void encode_and_print_dimacs() override;

protected:
    int max_width_SAT;
    int min_width_UNSAT;

    std::unordered_map<int, pid_t> work_pids;

    void create_work_pid(int width);
    int do_work_pid_task(int width);

    std::deque<int> search_order; // Stores the order of widths to search
    virtual std::deque<int> create_search_order() = 0;
    int get_next_width_to_search();
};
#endif