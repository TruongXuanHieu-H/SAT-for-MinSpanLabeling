#include "incre_instance_data.h"
#include "incre_encoder.h"
#include "incre_ladder.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"

#include <iostream>

IncreInstanceData::IncreInstanceData(GlobalData &global_data) : global_data(global_data) {};

IncreInstanceData::~IncreInstanceData()
{
    delete enc;
    delete cc;
    delete vh;
    delete solver;
};

std::string IncreInstanceData::get_signature()
{
    return "[Incremental]";
};

void IncreInstanceData::set_up_encoder()
{
    switch (global_data.encode_type)
    {
    case EncodeType::ladder:
        enc = new IncreLadder(*this);
        break;

    default:
        break;
    }
};

void IncreInstanceData::set_up_sat_solver()
{
    switch (global_data.sat_solver_type)
    {
    case SATSolverType::CaDiCaL:
        solver = new SATSolverCadical();
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
    cc = new ClauseContainer(solver);
    vh = new VarHandler(1, global_data.g->n * global_data.upper_bound);

    set_up_encoder();
}

void IncreInstanceData::cleanup_encoding()
{
    delete enc;
    enc = nullptr;
    delete cc;
    cc = nullptr;
    delete vh;
    vh = nullptr;
}

void IncreInstanceData::cleanup_solving()
{
    cleanup_encoding();

    delete solver;
    solver = nullptr;
}

void IncreInstanceData::export_dimacs(std::ostream &out)
{
    out << "c CNF fomular for graph " << global_data.g->graph_name << " with Antibandwidth value of " << global_data.target_value << "\n";
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