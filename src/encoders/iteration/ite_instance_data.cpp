#include "ite_instance_data.h"
#include "ite_ladder.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"

#include <iostream>

IteInstanceData::IteInstanceData(GlobalData &global_data, int label) : global_data(global_data), label(label) {};

IteInstanceData::~IteInstanceData() {};

std::string IteInstanceData::get_signature() { return "[Label = " + std::to_string(label) + "]"; };

void IteInstanceData::set_up_encoder()
{
    switch (global_data.encode_type)
    {
    case EncodeType::ladder:
        enc = std::make_unique<IteLadder>(*this);
        break;

    default:
        break;
    }
};

void IteInstanceData::set_up_sat_solver()
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

void IteInstanceData::setup_for_solving()
{
    set_up_sat_solver();

    setup_for_encoding();
}

void IteInstanceData::setup_for_encoding()
{
    cc = std::make_unique<ClauseContainer>(*solver);
    vh = std::make_unique<VarHandler>(1, global_data.g->n * label);

    set_up_encoder();
}

void IteInstanceData::export_dimacs(std::ostream &out)
{
    out << "c CNF fomular for graph " << global_data.g->graph_name << " with Cyclic Antibandwidth value of " << global_data.target_value << "\n";
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