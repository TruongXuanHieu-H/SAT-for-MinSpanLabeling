#ifndef CLAUSE_CONTAINER_H
#define CLAUSE_CONTAINER_H

#include "sat_solver.h"
#include <vector>

class ClauseContainer
{
public:
	ClauseContainer(SATSolver &solver);
	~ClauseContainer();

	std::vector<std::vector<int>> clause_list;

	void add_clause(const std::vector<int> &c);
	int size();

private:
	SATSolver &solver;
	void do_add_clause(const std::vector<int> &c);
	int do_size();
};

#endif
