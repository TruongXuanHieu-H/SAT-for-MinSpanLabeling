#ifndef ITE_FROM_UB_H
#define ITE_FROM_UB_H

#include "iteration.h"

class IteFromUB : public Iteration
{
public:
    IteFromUB();
    ~IteFromUB();

protected:
    std::deque<int> create_search_order() override;
};

#endif