#ifndef ITE_LADDER_CABP_H
#define ITE_LADDER_CABP_H

#include "ite_ladder.h"

#include <unordered_map>
#include <vector>

class IteLadderCABP : public IteLadder
{
public:
    IteLadderCABP() = default;
    ~IteLadderCABP() override = default;

    void encode_target_value(const IteInstanceData &) override;

    void encode_labels(const IteInstanceData &) override;
};

#endif