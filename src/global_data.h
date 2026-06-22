#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include "graph/graph.h"
#include "enum/encode_type.h"
#include "enum/problem_type.h"
#include "enum/sat_solver_type.h"
#include "enum/search_strategy.h"
#include "enum/symmetry_breaking_type.h"
#include "enum/vertices_mode.h"
#include <unordered_map>
#include <limits>

class GlobalData
{
public:
    GlobalData() {};
    ~GlobalData()
    {
        if (g)
        {
            delete g; // Clean up the global graph instance
            g = nullptr;
        }
    };

    Graph *g = nullptr;   // Pointer to the global graph instance
    int target_value = 0; // Target value for the problem (e.g., antibandwidth value for ABP)
    int lower_bound = 0;
    int upper_bound = 0;

    int worker_count = 1; // Does not matter if incremental is selected

    ProblemType problem_type = ProblemType::ABP;
    EncodeType encode_type = EncodeType::ladder;
    SearchStrategy search_strategy = SearchStrategy::iterate_bfs;
    SymmetryBreakingType symmetry_break_strategy = SymmetryBreakingType::NONE;
    SATSolverType sat_solver_type = SATSolverType::CaDiCaL;
    VerticesMode vertices_mode = VerticesMode::has_hole;

    bool just_print_dimacs = false;
    std::string dimacs_directory = "./dimacs_output/";

    bool enable_solution_verification = true;

    int sample_rate = 100000; // Interval of sampler, in microseconds
    int report_rate = 100;    // Interval of report, in number of sampler

    float memory_limit = std::numeric_limits<float>::max();       // bound of total memory consumed by all the processes, in megabyte
    float real_time_limit = std::numeric_limits<float>::max();    // bound of time consumed by main process, in seconds
    float elapsed_time_limit = std::numeric_limits<float>::max(); // bound of total time consumed by all the process, in seconds

    void read_graph(std::string graph_file_name)
    {
        g = new Graph(graph_file_name);
    };

    bool verbose = false; // If true, print more detailed information during the execution, such as the encoding details and the solving process. This is useful for debugging and understanding the behavior of the program, but it may produce a large amount of output for large instances.
};

#endif // GLOBAL_DATA_H