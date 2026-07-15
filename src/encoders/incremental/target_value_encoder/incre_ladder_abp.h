#ifndef INCRE_LADDER_ABP_H
#define INCRE_LADDER_ABP_H

#include "incre_target_value_encoder.h"

#include <unordered_map>
#include <vector>

struct VectorHash
{
    size_t operator()(const std::vector<int> &v) const
    {
        size_t hash = 0;

        for (int x : v)
        {
            hash ^= std::hash<int>()(x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }

        return hash;
    }
};

class IncreLadderABP : public IncreTargetValueEncoder
{
public:
    IncreLadderABP() = default;
    ~IncreLadderABP() override = default;

    void encode_target_value(const IncreInstanceData &) override;

    void encode_labels(const IncreInstanceData &) override;

private:
    std::unordered_map<std::vector<int>, int, VectorHash> target_value_aux_vars;

    int get_target_value_aux_var(const IncreInstanceData &, std::vector<int> key, bool is_key_exist = false);

    void encode_ladder(const IncreInstanceData &, const std::vector<int> ladder_vars, int width);
    void encode_window(const IncreInstanceData &, const std::vector<int> window_vars, bool is_first_window, bool is_last_window);
    void connect_windows(const IncreInstanceData &, const std::vector<int> first_window_vars, const std::vector<int> second_window_vars);
    void connect_ladder(const IncreInstanceData &, const std::vector<int> first_ladder_vars, const std::vector<int> second_ladder_vars, int width);
};

#endif