#ifndef ITE_INSTANCE_DATA_H
#define ITE_INSTANCE_DATA_H

#include "../general/clause_container.h"
#include "../general/var_handler.h"
#include "../general/sat_solver.h"
#include "../../graph/graph.h"

class IteEncoder;

class IteInstanceData
{
public:
    IteInstanceData(int target_value, int label);
    ~IteInstanceData();

    int target_value; // Width of the instance
    int label;

    IteEncoder *enc;
    ClauseContainer *cc;
    VarHandler *vh;
    SATSolver *solver;

    std::string get_signature();

    void set_up_encoder();
    void set_up_sat_solver();
    void setup_for_solving();
    void setup_for_encoding();
    void cleanup_encoding();
    void cleanup_solving();

    void export_dimacs(std::ostream &out);
};

#endif // INSTANCE_DATA_H