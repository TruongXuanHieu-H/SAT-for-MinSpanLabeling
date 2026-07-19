#ifndef ITE_BFS_REVERSE_H
#define ITE_BFS_REVERSE_H

#include "iteration.h"

class IteBFSReverse : public Iteration
{
public:
    IteBFSReverse(GlobalData &data);
    ~IteBFSReverse() override;

protected:
    std::deque<int> create_label_search_order() override;
};

#endif