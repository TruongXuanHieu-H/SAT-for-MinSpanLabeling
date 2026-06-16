#ifndef ITE_BFS_H
#define ITE_BFS_H

#include "iteration.h"

class IteBFS : public Iteration
{
public:
    IteBFS(int target_value, int lower_bound, int upper_bound);
    ~IteBFS() override;

protected:
    std::deque<int> create_label_search_order() override;
};

#endif