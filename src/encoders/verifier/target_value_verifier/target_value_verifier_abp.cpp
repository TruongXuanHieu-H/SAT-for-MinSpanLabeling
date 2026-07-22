#include "target_value_verifier_abp.h"

#include <assert.h>

int TargetValueVerifierABP::calculate_target_value(const Graph &g, const std::vector<int> &labels_assignment, const int span)
{
    assert(!labels_assignment.empty());

    return g.calculate_antibandwidth(labels_assignment);

    (void)span;
}