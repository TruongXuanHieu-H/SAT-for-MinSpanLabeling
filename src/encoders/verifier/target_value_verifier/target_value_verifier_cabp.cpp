#include "target_value_verifier_cabp.h"

#include <assert.h>

int TargetValueVerifierCABP::calculate_target_value(const Graph &g, const std::vector<int> &labels_assignment)
{
    assert(!labels_assignment.empty());

    return g.calculate_cyclic_antibandwidth(labels_assignment);
}