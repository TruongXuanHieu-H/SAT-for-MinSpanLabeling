#ifndef SAT_SOLVER_CADICAL_H
#define SAT_SOLVER_CADICAL_H

#include "sat_solver.h"
#include "../../../cadical-2.2.1/cadical.hpp"
#include <memory>

class SATSolverCadical : public SATSolver
{
public:
    SATSolverCadical();
    ~SATSolverCadical();

    void add_clause(const std::vector<int> &c) override;
    int solve() override;
    std::vector<int> extract_result(int num_vertices, int num_labels) override;

    std::unique_ptr<CaDiCaL::Solver> solver;
};

#endif // SAT_SOLVER_CADICAL_H