#ifndef ITE_INSTANCE_DATA_H
#define ITE_INSTANCE_DATA_H

#include "ite_encoder.h"
#include "../general/clause_container.h"
#include "../general/var_handler.h"
#include "../general/sat_solver.h"
#include "../../graph/graph.h"

class IteInstanceData
{
public:
    IteInstanceData();
    ~IteInstanceData();

    static int width; // Width of the instance

    static IteEncoder *enc;
    static ClauseContainer *cc;
    static VarHandler *vh;
    static SATSolver *solver;

    static std::string get_signature();

    static void set_up_encoder();
    static void set_up_sat_solver();
    static void setup_for_solving();
    static void setup_for_encoding();
    static void cleanup_encoding();
    static void cleanup_solving();

    static void export_dimacs(std::ostream &out);
};

#endif // INSTANCE_DATA_H