#ifndef TARGET_VALUE_VERIFIER_H
#define TARGET_VALUE_VERIFIER_H

#include "../../../graph/graph.h"

#include <vector>

class TargetValueVerifier
{
public:
    bool verify_target_value(const Graph &g, const int target_value, const std::vector<int> &labels_assignment)
    {
        if (calculate_target_value(g, labels_assignment) < target_value)
            return false;

        return true;
    }

protected:
    virtual int calculate_target_value(const Graph &g, const std::vector<int> &labels_assignment) = 0;
};

#endif