#include "iterative_instance_data.h"
#include "iterative_ladder_encoder.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"

#include <iostream>

IterativeInstanceData::~IterativeInstanceData()
{
    if (enc)
        delete enc;
    if (cc)
        delete cc;
    if (vh)
        delete vh;
    if (solver)
        delete solver;
}

int IterativeInstanceData::width = 0;

IterativeInstanceEncoder *IterativeInstanceData::enc = nullptr;
ClauseContainer *IterativeInstanceData::cc = nullptr;
VarHandler *IterativeInstanceData::vh = nullptr;
SATSolver *IterativeInstanceData::solver = nullptr;

std::string IterativeInstanceData::get_signature()
{
    return "[w = " + std::to_string(width) + "]";
};

void IterativeInstanceData::set_up_encoder()
{
    switch (GlobalData::encode_type)
    {
    case EncodeType::ladder:
        enc = new IterativeLadderEncoder();
        break;

    default:
        break;
    }
};

void IterativeInstanceData::set_up_sat_solver()
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

void IterativeInstanceData::setup_for_solving()
{
    set_up_sat_solver();

    setup_for_encoding();
}

void IterativeInstanceData::setup_for_encoding()
{
    cc = new ClauseContainer(solver);
    vh = new VarHandler(1, GlobalData::g->n);

    set_up_encoder();
}

void IterativeInstanceData::cleanup_encoding()
{
    delete enc;
    delete cc;
    delete vh;
}

void IterativeInstanceData::cleanup_solving()
{
    cleanup_encoding();

    delete solver;
}

void IterativeInstanceData::export_dimacs(std::ostream &out)
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