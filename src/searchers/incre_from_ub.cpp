#include "incre_from_ub.h"
#include "../global_data.h"
#include "../encoders/incremental/incre_instance.h"
#include "../utils/pid_manager.h"

#include <iostream>
#include <assert.h>
#include <sys/mman.h>
#include <cmath>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <chrono>

IncreFromUB::IncreFromUB(int target_value, int lower_bound, int upper_bound) : Searcher(target_value, lower_bound, upper_bound)
{
}

IncreFromUB::~IncreFromUB()
{
}

void IncreFromUB::encode_and_solve()
{
    fflush(stdout);
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();
    create_limit_pid();

    create_work_pid();

    int status;
    pid_t finished_pid = wait(&status); // Wait for the child to complete

    if (finished_pid == lim_pid)
    {
        std::cout << "c [Main] Lim pid ends with result: " << WEXITSTATUS(status) << ".\n";
        kill(work_pid, SIGTERM);
    }
    else if (finished_pid == work_pid)
    {
        std::cout << "c [Main] Work pid ends with result: " << WEXITSTATUS(status) << ".\n";
        kill(lim_pid, SIGTERM);
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "r [Main] \n";
    std::cout << "r [Main] Final results: \n";
    std::cout << "r [Main] Total real time: " << encode_duration << " ms.\n";
    std::cout << "r [Main] Total memory consumed: " << *max_consumed_memory << " MB.\n";
    std::cout << "r [Main] \n";
}

void IncreFromUB::encode_and_print_dimacs()
{
    std::cout << "e [Main] Print dimacs is currently not supported for incremental searchers.\n";
    exit(-1);
};

void IncreFromUB::create_work_pid()
{
    // std::cout << "p PID: " << getpid() << ", PPID: " << getppid() << ".\n";
    pid_t pid = fork();
    // std::cout << "q PID: " << getpid() << ", PPID: " << getppid() << ".\n";

    if (pid < 0)
    {
        std::cerr << "e [Main] Fork failed!\n";
        exit(-1);
    }
    else if (pid == 0)
    {
        prctl(PR_SET_PDEATHSIG, SIGTERM);
        std::cout << "c [Incremental] Start task in PID: " << getpid() << ".\n";

        IncreInstance instance(GlobalData::target_value, GlobalData::lower_bound, GlobalData::upper_bound);

        int result = instance.encode_and_solve_problem();

        std::cout
            << "c [Incremental] Result: " << result << ".\n";

        exit(result);
    }
    else
    {
        // Parent process stores the child's PID
        // std::cout << "c Child pid is tracked in PID: " << getpid() << ".\n";
        work_pid = pid;
    }
};