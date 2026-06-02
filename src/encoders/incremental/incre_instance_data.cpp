#include "incre_instance_data.h"
#include "incre_ladder.h"
#include "../general/sat_solver_cadical.h"
#include "../../global_data.h"

#include <iostream>

IncreInstanceData::~IncreInstanceData()
{
    delete enc;
    delete cc;
    delete vh;
    delete solver;
};

int IncreInstanceData::target_value = 0;
IncreEncoder *IncreInstanceData::enc = nullptr;
ClauseContainer *IncreInstanceData::cc = nullptr;
VarHandler *IncreInstanceData::vh = nullptr;
SATSolver *IncreInstanceData::solver = nullptr;

std::string IncreInstanceData::get_signature()
{
    return "[width = " + std::to_string(target_value) + "]";
};

void IncreInstanceData::set_up_encoder()
{
    switch (GlobalData::encode_type)
    {
    case EncodeType::ladder:
        enc = new IncreLadder();
        break;

    default:
        break;
    }
};