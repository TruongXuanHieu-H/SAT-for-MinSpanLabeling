#include "searcher.h"
#include "../global_data.h"
#include "../utils/pid_manager.h"

#include <iostream>
#include <assert.h>
#include <sys/mman.h>
#include <cmath>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <chrono>

Searcher::Searcher(GlobalData &data) : global_data(data)
{
    max_consumed_memory = (float *)mmap(nullptr, sizeof(float), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
}

Searcher::~Searcher()
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
int Searcher::is_limit_satisfied()
{
    if (consumed_memory > global_data.memory_limit)
        return -1;

    if (consumed_real_time > global_data.real_time_limit)
        return -2;

    if (consumed_elapsed_time > global_data.elapsed_time_limit)
        return -3;

    return 0;
}

void Searcher::create_limit_pid()
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
            consumed_real_time += std::round((float)global_data.sample_rate * 10 / 1000000.0) / 10;
            consumed_elapsed_time += (float)(global_data.sample_rate * (PIDManager::get_descendant_pids(main_pid).size() - 1)) / 1000000.0;

            if (consumed_memory > *max_consumed_memory)
            {
                *max_consumed_memory = consumed_memory;
                // std::cout << "[Lim] Memory consumed: " << max_consumed_memory << " MB.\n";
            }

            sampler_count++;
            if (sampler_count >= global_data.report_rate)
            {
                // std::cout << "c [Lim] Sampler:\t" << "Memory: " << consumed_memory << " MB\tReal time: " << consumed_real_time << "s\tElapsed time: " << consumed_elapsed_time << "s.\n";
                sampler_count = 0;
            }
            usleep(global_data.sample_rate);

            limit_state = is_limit_satisfied();
        }

        exit(limit_state);
    }
    else
    {
        // std::cout << "c Lim pid is forked at " << lim_pid << ".\n";
    }
}