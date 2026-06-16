#include "var_handler.h"

/*
 * input_size: number of nodes -> number of variables will be input_size^2
 */
VarHandler::VarHandler(int start_id, int input_size = 0) : first_assigned_id(start_id)
{
    next_to_assign = first_assigned_id + input_size;
    last_intput_var = next_to_assign - 1;
};

int VarHandler::get_new_var()
{
    return next_to_assign++;
};

int VarHandler::last_var() const
{
    return next_to_assign - 1;
};

int VarHandler::size() const
{
    return next_to_assign - first_assigned_id;
};