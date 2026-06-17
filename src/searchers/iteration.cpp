#include "iteration.h"
#include "../global_data.h"
#include "../encoders/iteration/ite_instance.h"
#include "../utils/pid_manager.h"

#include <iostream>
#include <assert.h>
#include <sys/mman.h>
#include <cmath>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <chrono>

Iteration::Iteration(GlobalData &data) : Searcher(data)
{
    lowest_label_SAT = global_data.upper_bound + 1;
    highest_label_UNSAT = global_data.lower_bound - 1;
}

Iteration::~Iteration()
{
    work_pids.clear();
}

void Iteration::encode_and_solve()
{
    fflush(stdout);
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    create_limit_pid();

    for (int i = 0; i < global_data.worker_count && i < (global_data.upper_bound + 1 - global_data.lower_bound); i += 1)
    {
        int next_label_to_search = get_next_label_to_search();
        if (next_label_to_search <= global_data.lower_bound - 1 || next_label_to_search >= global_data.upper_bound + 1)
        {
            break; // No valid label to search
        }
        else
        {
            create_work_pid(next_label_to_search);
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
                        if (it->first < lowest_label_SAT)
                        {
                            lowest_label_SAT = it->first;
                            std::cout << "c [Main] Lowest label SAT is set to " << it->first << ".\n";
                        }

                        for (auto ita = work_pids.begin(); ita != work_pids.end(); ita++)
                        {
                            // Pid with higher label than SAT pid is also SAT.
                            if (ita->first > it->first)
                            {
                                std::cout << "c [Main] Kill higher label pid " << ita->first << ".\n";
                                kill(ita->second, SIGTERM);
                            }
                        }
                        break;
                    case 20:
                        if (it->first > highest_label_UNSAT)
                        {
                            highest_label_UNSAT = it->first;
                            std::cout << "c [Main] Highest label UNSAT is set to " << it->first << "\n";
                        }

                        for (auto ita = work_pids.begin(); ita != work_pids.end(); ita++)
                        {
                            // Pid with lower label than UNSAT pid is also UNSAT.
                            if (ita->first < it->first)
                            {
                                std::cout << "c [Main] Kill lower label pid " << ita->first << ".\n";
                                kill(ita->second, SIGTERM);
                            }
                        }
                        break;
                    default:
                        break;
                    }

                    work_pids.erase(it);
                    if (work_pids.empty() && label_search_order.empty() && kill(lim_pid, 0) == 0)
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
            while (int(work_pids.size()) < global_data.worker_count)
            {
                int next_label_to_seach = get_next_label_to_search();
                if (next_label_to_seach <= global_data.lower_bound - 1 || next_label_to_seach >= global_data.upper_bound + 1)
                {
                    break; // No valid label to search
                }
                else
                {
                    create_work_pid(next_label_to_seach);
                }
            }

            if (work_pids.empty() && label_search_order.empty())
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
    std::cout << "r [Main] Lowest label SAT:  \t" << ((lowest_label_SAT == global_data.upper_bound + 1) ? "-" : std::to_string(lowest_label_SAT)) << ".\n";
    std::cout << "r [Main] Highest label UNSAT:\t" << ((highest_label_UNSAT == global_data.lower_bound - 1) ? "-" : std::to_string(highest_label_UNSAT)) << ".\n";
    std::cout << "r [Main] Total real time: " << encode_duration << " ms.\n";
    std::cout << "r [Main] Total memory consumed: " << *max_consumed_memory << " MB.\n";
    std::cout << "r [Main] \n";
}

void Iteration::encode_and_print_dimacs()
{
    for (int i = global_data.lower_bound; i <= global_data.upper_bound; i++)
    {
        IteInstance instance(global_data, i);
        instance.encode_and_print_dimacs();
    }
};

void Iteration::create_work_pid(int label)
{
    // std::cout << "p PID: " << getpid() << ", PPID: " << getppid() << ".\n";
    pid_t pid = fork();
    // std::cout << "q PID: " << getpid() << ", PPID: " << getppid() << ".\n";

    if (pid < 0)
    {
        std::cerr << "e [Label = " << label << "] Fork failed!\n";
        exit(-1);
    }
    else if (pid == 0)
    {
        prctl(PR_SET_PDEATHSIG, SIGTERM);
        std::cout << "c [Label = " << label << "] Start task in PID: " << getpid() << ".\n";

        // Child process: perform the task
        int result = do_work_pid_task(label);
        exit(result);
    }
    else
    {
        // Parent process stores the child's PID
        // std::cout << "c Child pid " << width << " - " << pid << " is tracked in PID: " << getpid() << ".\n";
        work_pids[label] = pid;
    }
}

int Iteration::do_work_pid_task(int label)
{
    // Dynamically allocate and use ABPEncoder in child process
    IteInstance instance(global_data, label);

    int result = instance.encode_and_solve_problem();

    std::cout << "c [Label = " << label << "] Result: " << result << ".\n";

    return result;
}

int Iteration::get_next_label_to_search()
{
    if (label_search_order.empty())
        return global_data.lower_bound - 1; // To terminate the search if no valid width is left. Value (global_data.upper_bound + 1) also works.

    int next_label = label_search_order.front();
    label_search_order.pop_front();

    while (next_label >= lowest_label_SAT || next_label <= highest_label_UNSAT)
    {

        if (label_search_order.empty())
            return global_data.lower_bound - 1; // To terminate the search if no valid width is left. Value (global_data.upper_bound + 1) also works.

        next_label = label_search_order.front();
        label_search_order.pop_front();
    }

    return next_label;
}
