#include "sat_solver_cadical.h"
#include "../../global_data.h"
#include <iostream>
#include <csignal>

SATSolverCadical::SATSolverCadical()
{
    solver = std::make_unique<CaDiCaL::Solver>();
    std::string sat_configuration = "sat";
    solver->configure(sat_configuration.data());
}

SATSolverCadical::~SATSolverCadical() {}

void SATSolverCadical::add_clause(const std::vector<int> &c)
{
    for (const auto &lit : c)
        solver->add(lit);
    solver->add(0);
}

int SATSolverCadical::solve()
{
    switch (solver->solve())
    {
    case 10:
        return 0;
    case 20:
        return 1;

    default:
        return -1;
    }
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