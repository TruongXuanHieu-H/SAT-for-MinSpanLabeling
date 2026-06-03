#ifndef INCRE_INSTANCE_DATA_H
#define INCRE_INSTANCE_DATA_H

#include "../general/clause_container.h"
#include "../general/var_handler.h"
#include "../general/sat_solver.h"
#include "../../graph/graph.h"

class IncreEncoder;

class IncreInstanceData
{
public:
    IncreInstanceData(int target_value, int lower_bound, int upper_bound);
    ~IncreInstanceData();

    int target_value = 0; // Width of the instance
    int lower_bound = 0;  // Lower bound of the search
    int upper_bound = 0;  // Upper bound of the search

    IncreEncoder *enc = nullptr;
    ClauseContainer *cc = nullptr;
    VarHandler *vh = nullptr;
    SATSolver *solver = nullptr;

    std::string get_signature();

    void set_up_encoder();
    void set_up_sat_solver();
    void setup_for_solving();
    void setup_for_encoding();
    void cleanup_encoding();
    void cleanup_solving();

    void export_dimacs(std::ostream &out);
};

#endif