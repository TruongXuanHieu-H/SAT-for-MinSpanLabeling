#include "mmsl_searcher.h"
#include "../global_data.h"
#include "../utils/pid_manager.h"

#include <iostream>
#include <assert.h>
#include <sys/mman.h>
#include <cmath>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <chrono>

MMSLSearcher::MMSLSearcher()
{
    max_consumed_memory = (float *)mmap(nullptr, sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    setup_bounds();
}

MMSLSearcher::~MMSLSearcher()
{
    munmap(max_consumed_memory, sizeof(float));
}

/*
 *  Check if limit conditions are satified or not
 *  Return:
 *      0   if all the conditions is satified.
 *      -1  if out of memory.
 *      -2  if out of real time.
 *      -3  if out of elapsed time.
 */
int MMSLSearcher::is_limit_satisfied()
{
    if (consumed_memory > GlobalData::memory_limit)
        return -1;

    if (consumed_real_time > GlobalData::real_time_limit)
        return -2;

    if (consumed_elapsed_time > GlobalData::elapsed_time_limit)
        return -3;

    return 0;
}

void MMSLSearcher::setup_bounds()
{
    lookup_bounds();
    override_bounds();

    assert((lower_bound >= 2) && (lower_bound <= upper_bound) && (upper_bound <= GlobalData::g->n / 2));
}

void MMSLSearcher::lookup_bounds()
{
    lookup_lower_bound();
    lookup_upper_bound();
}

void MMSLSearcher::lookup_upper_bound()
{
    auto pos = GlobalData::mmsl_UBs.find(GlobalData::g->graph_name);
    if (pos != GlobalData::mmsl_UBs.end())
    {
        upper_bound = pos->second;
        std::cout << "c [Main] Upper bound is set to " << upper_bound << ".\n";
    }
    else
    {
        upper_bound = GlobalData::g->n / 2;
        std::cout << "c [Main] No predefined upper bound is found for " << GlobalData::g->graph_name << ".\n";
        std::cout << "c [Main] UB-w = " << upper_bound << " (default value calculated as n/2).\n";
    }
}

void MMSLSearcher::lookup_lower_bound()
{
    auto pos = GlobalData::mmsl_LBs.find(GlobalData::g->graph_name);
    if (pos != GlobalData::mmsl_LBs.end())
    {
        lower_bound = pos->second;
        std::cout << "c [Main] Lower bound is set to " << lower_bound << ".\n";
    }
    else
    {
        lower_bound = 2;
        std::cout << "c [Main] No predefined lower bound is found for " << GlobalData::g->graph_name << ".\n";
        std::cout << "c [Main] LB-w = 2 (default value).\n";
    }
}

void MMSLSearcher::override_bounds()
{
    override_lower_bound();
    override_upper_bound();
}

void MMSLSearcher::override_lower_bound()
{
    if (GlobalData::overwrite_lb)
    {
        std::cout << "c [Main] LB " << lower_bound << " is overwritten with " << GlobalData::forced_lb << ".\n";
        lower_bound = GlobalData::forced_lb;
    }
}

void MMSLSearcher::override_upper_bound()
{
    if (GlobalData::overwrite_ub)
    {
        std::cout << "c [Main] UB " << upper_bound << " is overwritten with " << GlobalData::forced_ub << ".\n";
        upper_bound = GlobalData::forced_ub;
    }
}

void MMSLSearcher::create_limit_pid()
{
    lim_pid = fork();
    if (lim_pid < 0)
    {
        std::cerr << "e [Lim] Fork Failed!\n";
        exit(-1);
    }
    else if (lim_pid == 0)
    {
        pid_t main_pid = getppid();
        int limit_state = is_limit_satisfied();

        while (limit_state == 0)
        {
            consumed_memory = std::round(PIDManager::get_total_memory_usage(main_pid) * 10 / 1024.0) / 10;
            consumed_real_time += std::round((float)GlobalData::sample_rate * 10 / 1000000.0) / 10;
            consumed_elapsed_time += (float)(GlobalData::sample_rate * (PIDManager::get_descendant_pids(main_pid).size() - 1)) / 1000000.0;

            if (consumed_memory > *max_consumed_memory)
            {
                *max_consumed_memory = consumed_memory;
                // std::cout << "[Lim] Memory consumed: " << max_consumed_memory << " MB.\n";
            }

            sampler_count++;
            if (sampler_count >= GlobalData::report_rate)
            {
                // std::cout << "c [Lim] Sampler:\t" << "Memory: " << consumed_memory << " MB\tReal time: " << consumed_real_time << "s\tElapsed time: " << consumed_elapsed_time << "s.\n";
                sampler_count = 0;
            }
            usleep(GlobalData::sample_rate);

            limit_state = is_limit_satisfied();
        }

        exit(limit_state);
    }
    else
    {
        // std::cout << "c Lim pid is forked at " << lim_pid << ".\n";
    }
}