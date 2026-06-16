#ifndef ITERATION_H
#define ITERATION_H

#include "searcher.h"

class Iteration : public Searcher
{
public:
    Iteration(int target_value, int lower_bound, int upper_bound);
    ~Iteration();

    void encode_and_solve() override;
    void encode_and_print_dimacs() override;

protected:
    int lowest_label_SAT;
    int highest_label_UNSAT;

    std::unordered_map<int, pid_t> work_pids;

    void create_work_pid(int label);
    int do_work_pid_task(int label);

    std::deque<int> label_search_order; // Stores the order of labels to search
    virtual std::deque<int> create_label_search_order() = 0;
    int get_next_label_to_search();
};
#endif