#include "clause_container.h"
#include <iostream>

ClauseContainer::ClauseContainer(SATSolver *solver)
{
    this->solver = solver;
};

ClauseContainer::~ClauseContainer() {};

void ClauseContainer::add_clause(const std::vector<int> &c)
{
    do_add_clause(c);
};

int ClauseContainer::size()
{
    return do_size();
};

void ClauseContainer::do_add_clause(const std::vector<int> &c)
{
    clause_list.push_back(c);
    solver->add_clause(c);
};

int ClauseContainer::do_size()
{
    return clause_list.size();
};
