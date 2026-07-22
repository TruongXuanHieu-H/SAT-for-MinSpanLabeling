#ifndef ITE_INSTANCE_H
#define ITE_INSTANCE_H

#include "ite_instance_data.h"
#include "../../global_data.h"
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
    int SAT_res = 0;

    std::unique_ptr<IteInstanceData> instance_data;
};

#endif