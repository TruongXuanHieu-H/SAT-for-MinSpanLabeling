#ifndef TARGET_VALUE_VERIFIER_CABP_H
#define TARGET_VALUE_VERIFIER_CABP_H

#include "target_value_verifier.h"

class TargetValueVerifierCABP : public TargetValueVerifier
{
protected:
    int calculate_target_value(const Graph &g, const std::vector<int> &labels_assignment) override;
};

#endif