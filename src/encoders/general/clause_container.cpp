#include "clause_container.h"
#include "../../global_data.h"
#include "assert.h"
#include <iostream>

ClauseContainer::ClauseContainer(GlobalData &global_data, VarHandler &var_handler, SATSolver &solver)
    : global_data(global_data), var_handler(var_handler), solver(solver) {}

ClauseContainer::~ClauseContainer() {}

void ClauseContainer::add_clause(const std::vector<int> &c)
{
    assert(global_data.max_cnf_size >= 0);
    if (global_data.max_cnf_size == 0)
        do_add_clause(c);
    else
    {
        std::vector<int> long_clause = c;
        while ((int)long_clause.size() > global_data.max_cnf_size)
        {
            int split_var = var_handler.get_new_var();

            std::vector<int> chunk(long_clause.begin(), long_clause.begin() + global_data.max_cnf_size);
            chunk.push_back(split_var);
            do_add_clause(chunk);

            std::vector<int> rest = {-1 * split_var};
            rest.insert(rest.end(), long_clause.begin() + global_data.max_cnf_size, long_clause.end());
            long_clause = rest;
        }
        do_add_clause(long_clause);
    }
}

int ClauseContainer::size() { return do_size(); }

void ClauseContainer::do_add_clause(const std::vector<int> &c)
{
    clause_list.push_back(c);
    solver.add_clause(c);
}

int ClauseContainer::do_size() { return clause_list.size(); }
