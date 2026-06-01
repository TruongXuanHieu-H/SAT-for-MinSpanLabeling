#include "mmsl_iterate.h"
#include "../global_data.h"
#include "../encoders/iterative/iterative_mmsl_instance.h"
#include "../utils/pid_manager.h"

#include <iostream>
#include <assert.h>
#include <sys/mman.h>
#include <cmath>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <chrono>

MMSLIterate::MMSLIterate() : MMSLSearcher()
{
    max_width_SAT = lower_bound - 1;
    min_width_UNSAT = upper_bound + 1;
}

MMSLIterate::~MMSLIterate()
{
    work_pids.clear();
}

void MMSLIterate::encode_and_solve()
{
    fflush(stdout);
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    create_limit_pid();

    for (int i = 0; i < GlobalData::worker_count && i < (upper_bound + 1 - lower_bound); i += 1)
    {
        int next_width_to_seach = get_next_width_to_search();
        if (next_width_to_seach <= lower_bound - 1 || next_width_to_seach >= upper_bound + 1)
        {
            break; // No valid width to search
        }
        else
        {
            create_work_pid(next_width_to_seach);
        }
    }

    bool limit_violated = false;

    // Parent process waits until all child processes finish
    while (!work_pids.empty())
    {
        int status;
        pid_t finished_pid = wait(&status); // Wait for any child to complete

        if (finished_pid == lim_pid)
        {
            limit_violated = true;
            std::cout << "c [Main] Lim pid ends with result: " << WEXITSTATUS(status) << ".\n";
            while (!work_pids.empty())
            {
                kill(work_pids.begin()->second, SIGTERM);
                work_pids.erase(work_pids.begin());
            }
        }
        else if (WIFEXITED(status))
        {
            // Remove the finished child from the map
            for (auto it = work_pids.begin(); it != work_pids.end(); ++it)
            {
                if (it->second == finished_pid)
                {
                    // std::cout << "c Child pid " << it->first << " - " << it->second << " exited with status " << WEXITSTATUS(status) << ".\n";

                    switch (WEXITSTATUS(status))
                    {
                    case 10:
                        if (it->first > max_width_SAT)
                        {
                            max_width_SAT = it->first;
                            std::cout << "c [Main] Max width SAT is set to " << it->first << ".\n";
                        }

                        for (auto ita = work_pids.begin(); ita != work_pids.end(); ita++)
                        {
                            // Pid with lower width than SAT pid is also SAT.
                            if (ita->first < it->first)
                            {
                                std::cout << "c [Main] Kill lower pid " << ita->first << ".\n";
                                kill(ita->second, SIGTERM);
                            }
                        }
                        break;
                    case 20:
                        if (it->first < min_width_UNSAT)
                        {
                            min_width_UNSAT = it->first;
                            std::cout << "c [Main] Min width UNSAT is set to " << it->first << "\n";
                        }

                        for (auto ita = work_pids.begin(); ita != work_pids.end(); ita++)
                        {
                            // Pid with higher width than UNSAT pid is also UNSAT.
                            if (ita->first > it->first)
                            {
                                std::cout << "c [Main] Kill higher pid " << ita->first << ".\n";
                                kill(ita->second, SIGTERM);
                            }
                        }
                        break;
                    default:
                        break;
                    }

                    work_pids.erase(it);
                    if (work_pids.empty() && search_order.empty() && kill(lim_pid, 0) == 0)
                    {
                        kill(lim_pid, SIGTERM);
                    }
                    break;
                }
            }
        }
        else if (WIFSIGNALED(status))
        {
            // Remove the terminated child from the map
            for (auto it = work_pids.begin(); it != work_pids.end(); ++it)
            {
                if (it->second == finished_pid)
                {
                    std::cout << "c [Main] Child pid " << it->first << " - " << it->second << " terminated by signal " << WTERMSIG(status) << ".\n";
                    work_pids.erase(it);
                    if (work_pids.empty() && kill(lim_pid, 0) == 0)
                    {
                        kill(lim_pid, SIGTERM);
                    }
                    break;
                }
            }
        }
        else
        {
            for (auto it = work_pids.begin(); it != work_pids.end(); ++it)
            {
                if (it->second == finished_pid)
                {
                    std::cerr << "e [Main] Child pid " << it->first << " - " << it->second << " stopped or otherwise terminated.\n";
                    work_pids.erase(it);
                    if (work_pids.empty() && kill(lim_pid, 0) == 0)
                    {
                        kill(lim_pid, SIGTERM);
                    }
                    break;
                }
            }
        }

        if (!limit_violated)
        {
            fflush(stdout);
            while (int(work_pids.size()) < GlobalData::worker_count)
            {
                int next_width_to_seach = get_next_width_to_search();
                if (next_width_to_seach <= lower_bound - 1 || next_width_to_seach >= upper_bound + 1)
                {
                    break; // No valid width to search
                }
                else
                {
                    create_work_pid(next_width_to_seach);
                }
            }

            if (work_pids.empty() && search_order.empty())
            {
                kill(lim_pid, SIGTERM);
            }
        }
    }
    std::cout << "c [Main] All children have completed.\n";

    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "r [Main] \n";
    std::cout << "r [Main] Final results: \n";
    std::cout << "r [Main] Max width SAT:  \t" << ((max_width_SAT == lower_bound - 1) ? "-" : std::to_string(max_width_SAT)) << ".\n";
    std::cout << "r [Main] Min width UNSAT:\t" << ((min_width_UNSAT == upper_bound + 1) ? "-" : std::to_string(min_width_UNSAT)) << ".\n";
    std::cout << "r [Main] Total real time: " << encode_duration << " ms.\n";
    std::cout << "r [Main] Total memory consumed: " << *max_consumed_memory << " MB.\n";
    std::cout << "r [Main] \n";
}

void MMSLIterate::encode_and_print_dimacs()
{
    for (int i = lower_bound; i <= upper_bound; i++)
    {
        IterativeMMSLInstance msl_instance(i);
        msl_instance.encode_and_print_dimacs();
    }
};

void MMSLIterate::create_work_pid(int width)
{
    // std::cout << "p PID: " << getpid() << ", PPID: " << getppid() << ".\n";
    pid_t pid = fork();
    // std::cout << "q PID: " << getpid() << ", PPID: " << getppid() << ".\n";

    if (pid < 0)
    {
        std::cerr << "e [w = " << width << "] Fork failed!\n";
        exit(-1);
    }
    else if (pid == 0)
    {
        prctl(PR_SET_PDEATHSIG, SIGTERM);
        std::cout << "c [w = " << width << "] Start task in PID: " << getpid() << ".\n";

        // Child process: perform the task
        int result = do_work_pid_task(width);

        exit(result);
    }
    else
    {
        // Parent process stores the child's PID
        // std::cout << "c Child pid " << width << " - " << pid << " is tracked in PID: " << getpid() << ".\n";
        work_pids[width] = pid;
    }
}

int MMSLIterate::do_work_pid_task(int width)
{
    // Dynamically allocate and use ABPEncoder in child process
    IterativeMMSLInstance msl_instance(width);

    int result = msl_instance.encode_and_solve_problem();

    std::cout << "c [w = " << width << "] Result: " << result << ".\n";

    // std::cout << "c [w = " << width << "] Child " << width << " completed task.\n";
    return result;
}

int MMSLIterate::get_next_width_to_search()
{
    if (search_order.empty())
        return lower_bound - 1; // To terminate the search if no valid width is left. Value (upper_bound + 1) also works.

    int next_width = search_order.front();
    search_order.pop_front();

    while (next_width <= max_width_SAT || next_width >= min_width_UNSAT)
    {
        if (search_order.empty())
            return lower_bound - 1; // To terminate the search if no valid width is left. Value (upper_bound + 1) also works.

        next_width = search_order.front();
        search_order.pop_front();
    }

    return next_width;
}
