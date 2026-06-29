#include "args_parser.h"
#include "../global_data.h"
#include "iostream"
#include "stdexcept"
#include "usage.h"

ArgsParser::ArgsParser(GlobalData &data) : globalData(data)
{
    init_parser();
}

ArgsParser::~ArgsParser() {}

void ArgsParser::init_parser()
{
    cmd["--abp"] = [this](int, int, char **)
    {
        globalData.problem_type = ProblemType::ABP;
    };

    cmd["--cabp"] = [this](int, int, char **)
    {
        globalData.problem_type = ProblemType::CyclicABP;
    };

    cmd["--ladder"] = [this](int, int, char **)
    {
        globalData.encode_type = EncodeType::ladder;
    };

    cmd["--verify-result"] = [this](int, int, char **)
    {
        globalData.enable_solution_verification = true;
    };

    cmd["--incremental-from-ub"] = [this](int, int, char **)
    {
        globalData.search_strategy = SearchStrategy::incremental_from_ub;
    };

    cmd["--iterate-bfs"] = [this](int, int, char **)
    {
        globalData.search_strategy = SearchStrategy::iterate_bfs;
    };

    cmd["--iterate-from-ub"] = [this](int, int, char **)
    {
        globalData.search_strategy = SearchStrategy::iterate_from_ub;
    };

    cmd["-target-value"] = [this](int &i, int argc, char **argv)
    {
        globalData.target_value = get_positive(i, argc, argv, "target value");
    };

    cmd["-set-lb"] = [this](int &i, int argc, char **argv)
    {
        globalData.lower_bound = get_positive(i, argc, argv, "lower bound");

        std::cout << "c [Param] LB is predefined as " << globalData.lower_bound << ".\n";
    };

    cmd["-set-ub"] = [this](int &i, int argc, char **argv)
    {
        globalData.upper_bound = get_positive(i, argc, argv, "upper bound");

        std::cout << "c [Param] UB is predefined as " << globalData.upper_bound << ".\n";
    };

    cmd["-limit-memory"] = [this](int &i, int argc, char **argv)
    {
        globalData.memory_limit = get_positive(i, argc, argv, "memory limit");
        std::cout << "c [Param] Memory limit is set to " << globalData.memory_limit << ".\n";
    };

    cmd["-limit-real-time"] = [this](int &i, int argc, char **argv)
    {
        globalData.real_time_limit = get_positive(i, argc, argv, "real time limit");
        std::cout << "c [Param] Real time limit is set to " << globalData.real_time_limit << ".\n";
    };

    cmd["-limit-elapsed-time"] = [this](int &i, int argc, char **argv)
    {
        globalData.elapsed_time_limit = get_positive(i, argc, argv, "elapsed time limit");
        std::cout << "c [Param] Elapsed time limit is set to " << globalData.elapsed_time_limit << ".\n";
    };

    cmd["-sample-rate"] = [this](int &i, int argc, char **argv)
    {
        globalData.sample_rate = get_positive(i, argc, argv, "sample rate");
        std::cout << "c [Param] Sample rate is set to " << globalData.sample_rate << ".\n";
    };

    cmd["-report-rate"] = [this](int &i, int argc, char **argv)
    {
        globalData.report_rate = get_positive(i, argc, argv, "report rate");
        std::cout << "c [Param] Report rate is set to " << globalData.report_rate << ".\n";
    };

    cmd["-worker-count"] = [this](int &i, int argc, char **argv)
    {
        globalData.worker_count = get_positive(i, argc, argv, "worker count");
        std::cout << "c [Param] Worker count is set to " << globalData.worker_count << ".\n";
    };

    cmd["-symmetry-break"] = [this](int &i, int argc, char **argv)
    {
        if (i + 1 >= argc)
            throw std::runtime_error("Missing symmetry type");

        std::string s = argv[++i];

        if (s == "none")
            globalData.symmetry_break_strategy = SymmetryBreakingType::NONE;
        else if (s == "first")
            globalData.symmetry_break_strategy = SymmetryBreakingType::FIRST;
        else if (s == "highest-degree")
            globalData.symmetry_break_strategy = SymmetryBreakingType::HIGHEST_DEGREE;
        else if (s == "lowest-degree")
            globalData.symmetry_break_strategy = SymmetryBreakingType::LOWEST_DEGREE;
        else
            throw std::runtime_error("Unrecognized symmetry breaking type: " + s);
    };

    cmd["-sat-solver"] = [this](int &i, int argc, char **argv)
    {
        if (i + 1 >= argc)
            throw std::runtime_error("Missing solver type");

        std::string s = argv[++i];

        if (s == "cadical")
            globalData.sat_solver_type = SATSolverType::CaDiCaL;
        else
            throw std::runtime_error("Unrecognized SAT solver type: " + s);
    };

    cmd["-just-print-dimacs"] = [this](int &i, int argc, char **argv)
    {
        if (i + 1 >= argc)
            throw std::runtime_error("Missing directory");

        globalData.just_print_dimacs = true;
        globalData.dimacs_directory = argv[++i];
    };

    cmd["--verbose"] = [this](int, int, char **)
    {
        globalData.verbose = true;
    };

    cmd["--has-hole"] = [this](int, int, char **)
    {
        globalData.vertices_mode = VerticesMode::has_hole;
    };

    cmd["--no-hole"] = [this](int, int, char **)
    {
        globalData.vertices_mode = VerticesMode::no_hole;
    };

    cmd["-max-cnf-size"] = [this](int &i, int argc, char **argv)
    {
        globalData.max_cnf_size = get_positive(i, argc, argv, "max cnf size");
        std::cout << "c [Param] Max CNF size is set to " << globalData.max_cnf_size << ".\n";
    };
}

int ArgsParser::try_parse_args(int argc, char **argv)
{
    try
    {
        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];

            if (arg[0] != '-')
            {
                globalData.read_graph(arg);
                continue;
            }

            auto it = cmd.find(arg);
            if (it != cmd.end())
            {
                it->second(i, argc, argv);
            }
            else if (arg == "--help")
            {
                Helper::print_usage();
                return 1;
            }
            else
            {
                throw std::runtime_error("Unrecognized option: " + arg);
            }
        }
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "e [Param] " << e.what() << "\n";
        return -1;
    }
}

int ArgsParser::get_int(const std::string &arg)
{
    try
    {
        return std::stoi(arg);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Invalid number: " + arg);
    }
}

int ArgsParser::get_positive(int &i, int argc, char **argv, const std::string &name)
{
    if (i + 1 >= argc)
        throw std::runtime_error("Missing value for " + name);
    int val = get_int(argv[++i]);
    if (val <= 0)
        throw std::runtime_error(name + " must be positive");
    return val;
}
