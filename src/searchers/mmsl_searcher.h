#ifndef MMSL_SEARCHER_H
#define MMSL_SEARCHER_H

#include <unordered_map>
#include <unistd.h>
#include <deque>

class MMSLSearcher
{
public:
    MMSLSearcher();
    virtual ~MMSLSearcher();

    virtual void encode_and_solve() = 0;
    virtual void encode_and_print_dimacs() = 0;

protected:
    int lower_bound;
    int upper_bound;

    pid_t lim_pid;

    int sampler_count = 0;

    float *max_consumed_memory;
    float consumed_memory = 0;       // total memory consumed by all the processes, in megabyte
    float consumed_real_time = 0;    // time consumed by main process, in seconds
    float consumed_elapsed_time = 0; // total time consumed by all the process, in seconds

    int is_limit_satisfied();

    void setup_bounds();
    void lookup_bounds();
    void lookup_lower_bound();
    void lookup_upper_bound();
    void override_bounds();
    void override_lower_bound();
    void override_upper_bound();

    void create_limit_pid();
};
#endif