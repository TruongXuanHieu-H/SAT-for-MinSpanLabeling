#include "incre_instance_data.h"
#include "incre_encoder.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"

#include <iostream>

IncreInstanceData::IncreInstanceData(GlobalData &global_data) : global_data(global_data) {};

IncreInstanceData::~IncreInstanceData() {};

std::string IncreInstanceData::get_signature() { return "[Incremental]"; };

void IncreInstanceData::set_up_encoder()
{
    enc = std::make_unique<IncreEncoder>(*this);
}

void IncreInstanceData::set_up_sat_solver()
{
    switch (global_data.sat_solver_type)
    {
    case SATSolverType::CaDiCaL:
        solver = std::make_unique<SATSolverCadical>();
        break;

    default:
        break;
    }
};

void IncreInstanceData::setup_for_solving()
{
    set_up_sat_solver();

    setup_for_encoding();
}

void IncreInstanceData::setup_for_encoding()
{
    vh = std::make_unique<VarHandler>(1, global_data.g->n * global_data.upper_bound);
    cc = std::make_unique<ClauseContainer>(global_data, *vh, *solver);

    set_up_encoder();
}

void IncreInstanceData::export_dimacs(std::ostream &out)
{
    out << "c CNF fomular for graph " << global_data.g->graph_name << " with target value of " << global_data.target_value << "\n";
    out << "p cnf " << vh->size() << " " << cc->size() << "\n";
    for (const std::vector<int> &c : cc->clause_list)
    {
        for (int lit : c)
        {
            out << lit << " ";
        }
        out << "0\n";
    }
}