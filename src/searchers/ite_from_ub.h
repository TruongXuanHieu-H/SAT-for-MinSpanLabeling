#ifndef ITE_FROM_UB_H
#define ITE_FROM_UB_H

#include "iteration.h"

class IteFromUB : public Iteration
{
public:
    IteFromUB(int target_value, int lower_bound, int upper_bound);
    ~IteFromUB() override;

protected:
    std::deque<int> create_label_search_order() override;
};

#endif