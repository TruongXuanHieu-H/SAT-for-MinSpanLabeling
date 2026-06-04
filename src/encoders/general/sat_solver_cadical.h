#ifndef SAT_SOLVER_CADICAL_H
#define SAT_SOLVER_CADICAL_H

#include "sat_solver.h"
#include "../../../cadical-2.2.1/cadical.hpp"

class SATSolverCadical : public SATSolver
{
public:
    SATSolverCadical();
    ~SATSolverCadical();

    void set_up_solver() override;
    void add_clause(const std::vector<int> &c) override;
    int solve() override;
    std::vector<int> extract_result(int num_vertices, int num_labels) override;
    void clear_solver() override;

    CaDiCaL::Solver *solver;
};

#endif // SAT_SOLVER_CADICAL_H