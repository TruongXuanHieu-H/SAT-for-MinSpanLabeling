#ifndef ITE_INSTANCE_DATA_H
#define ITE_INSTANCE_DATA_H

#include "../general/clause_container.h"
#include "../general/var_handler.h"
#include "../general/sat_solver.h"
#include "../../global_data.h"
#include "../../graph/graph.h"
#include <memory>

class IteEncoder;

class IteInstanceData
{
public:
    IteInstanceData(GlobalData &global_data, int label);
    ~IteInstanceData();

    GlobalData &global_data;
    int label;

    std::unique_ptr<IteEncoder> enc;
    std::unique_ptr<ClauseContainer> cc;
    std::unique_ptr<VarHandler> vh;
    std::unique_ptr<SATSolver> solver;

    std::string get_signature();

    void set_up_encoder();
    void set_up_sat_solver();
    void setup_for_solving();
    void setup_for_encoding();

    void export_dimacs(std::ostream &out);
};

#endif