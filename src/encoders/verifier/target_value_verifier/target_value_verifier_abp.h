#ifndef TARGET_VALUE_VERIFIER_ABP_H
#define TARGET_VALUE_VERIFIER_ABP_H

#include "target_value_verifier.h"

class TargetValueVerifierABP : public TargetValueVerifier
{
protected:
    int calculate_target_value(const Graph &g, const std::vector<int> &labels_assignment) override;
};

#endif