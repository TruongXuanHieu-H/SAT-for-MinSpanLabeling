#ifndef INCRE_INSTANCE_H
#define INCRE_INSTANCE_H

#include "incre_instance_data.h"
#include "../../global_data.h"
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
    GlobalData &global_data;
    std::unique_ptr<IncreInstanceData> instance_data;
};

#endif