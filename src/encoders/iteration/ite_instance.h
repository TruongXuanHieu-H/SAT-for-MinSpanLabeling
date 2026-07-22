#ifndef ITE_INSTANCE_H
#define ITE_INSTANCE_H

#include "ite_instance_data.h"
#include "../../global_data.h"
#include "../verifier/verifier.h"
#include <limits>
#include <memory>

class IteInstance
{
public:
    IteInstance(GlobalData &global_data, int label);
    virtual ~IteInstance();

    int encode_and_solve_problem();
    void encode_and_print_dimacs();

private:
    IteInstanceData instance_data;
    Verifier verifier;
};

#endif