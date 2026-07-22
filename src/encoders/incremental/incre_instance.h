#ifndef INCRE_INSTANCE_H
#define INCRE_INSTANCE_H

#include "incre_instance_data.h"
#include "../../global_data.h"
#include "../verifier/verifier.h"
#include <limits>
#include <memory>

class IncreInstance
{
public:
    IncreInstance(GlobalData &global_data);
    virtual ~IncreInstance();

    int encode_and_solve_problem();
    void encode_and_print_dimacs();

private:
    IncreInstanceData instance_data;
    Verifier verifier;
};

#endif