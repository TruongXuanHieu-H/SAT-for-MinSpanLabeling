#ifndef ITE_LADDER_ABP_H
#define ITE_LADDER_ABP_H

#include "ite_ladder.h"

#include <unordered_map>
#include <vector>

class IteLadderABP : public IteLadder
{
public:
    IteLadderABP() = default;
    ~IteLadderABP() override = default;

    void encode_target_value(const IteInstanceData &) override;

    void encode_labels(const IteInstanceData &) override;
};

#endif