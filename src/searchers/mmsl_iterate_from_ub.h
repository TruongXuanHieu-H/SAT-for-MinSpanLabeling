#ifndef MMSL_ITERATE_FROM_UB_H
#define MMSL_ITERATE_FROM_UB_H

#include "mmsl_iterate.h"

class MMSLIterateFromUB : public MMSLIterate
{
public:
    MMSLIterateFromUB();
    ~MMSLIterateFromUB();

protected:
    std::deque<int> create_search_order() override;
};

#endif