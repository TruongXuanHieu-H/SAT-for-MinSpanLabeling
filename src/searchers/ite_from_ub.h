#ifndef ITE_FROM_UB_H
#define ITE_FROM_UB_H

#include "iteration.h"

class IteFromUB : public Iteration
{
public:
    IteFromUB(GlobalData &data);
    ~IteFromUB() override;

protected:
    std::deque<int> create_label_search_order() override;
};

#endif