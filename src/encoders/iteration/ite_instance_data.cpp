#include "ite_instance_data.h"
#include "ite_ladder.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"

#include <iostream>

IteInstanceData::~IteInstanceData()
{
    delete enc;
    delete cc;
    delete vh;
    delete solver;
}

int IteInstanceData::width = 0;

IteEncoder *IteInstanceData::enc = nullptr;
ClauseContainer *IteInstanceData::cc = nullptr;
VarHandler *IteInstanceData::vh = nullptr;
SATSolver *IteInstanceData::solver = nullptr;

std::string IteInstanceData::get_signature()
{
    return "[w = " + std::to_string(width) + "]";
};

void IteInstanceData::set_up_encoder()
{
    switch (GlobalData::encode_type)
    {
    case EncodeType::ladder:
        enc = new IteLadder();
        break;

    default:
        break;
    }
};

void IteInstanceData::set_up_sat_solver()
{
    switch (GlobalData::sat_solver_type)
    {
    case SATSolverType::CaDiCaL:
        solver = new SATSolverCadical();
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
    cc = new ClauseContainer(solver);
    vh = new VarHandler(1, GlobalData::g->n);

    set_up_encoder();
}

void IteInstanceData::cleanup_encoding()
{
    delete enc;
    delete cc;
    delete vh;
}

void IteInstanceData::cleanup_solving()
{
    cleanup_encoding();

    delete solver;
}

void IteInstanceData::export_dimacs(std::ostream &out)
{
    out << "c CNF fomular for graph " << GlobalData::g->graph_name << " with Cyclic Antibandwidth value of " << width << "\n";
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