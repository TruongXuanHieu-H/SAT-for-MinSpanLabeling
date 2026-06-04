#include "sat_solver_cadical.h"
#include "../../global_data.h"
#include <iostream>
#include <csignal>

SATSolverCadical::SATSolverCadical()
{
    set_up_solver();
}

SATSolverCadical::~SATSolverCadical()
{
    clear_solver();
}

void SATSolverCadical::set_up_solver()
{
    solver = new CaDiCaL::Solver();
    std::cout << "c [Solver] Initializing CaDiCaL (version " << solver->version() << ").\n";
    std::string sat_configuration = "sat";
    int res = solver->configure(sat_configuration.data());
    std::cout << "c [Solver] Configuring CaDiCaL as --" << sat_configuration << " (" << res << ").\n";
}

void SATSolverCadical::clear_solver()
{
    delete solver;
    solver = nullptr;
}

void SATSolverCadical::add_clause(const std::vector<int> &c)
{
    for (const auto &lit : c)
    {
        solver->add(lit);
    }
    solver->add(0);
}

int SATSolverCadical::solve()
{
    return solver->solve();
}

std::vector<int> SATSolverCadical::extract_result(int num_vertices, int num_labels)
{
    std::vector<int> result(num_vertices, 0);
    for (int vertex = 0; vertex < num_vertices; ++vertex)
    {
        for (int label = 1; label <= num_labels; ++label)
        {
            int res = solver->val(vertex * num_labels + label);
            if (res > 0)
            {
                if (result[vertex] != 0)
                {
                    std::cerr << "e " << " Error, the solution is not a labelling: more than one label assigned for vertex " << vertex + 1 << ".\n";
                    raise(SIGABRT);
                }
                result[vertex] = label;
            }
        }
    }

    return result;
}
