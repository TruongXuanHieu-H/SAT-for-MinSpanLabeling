#ifndef ITE_LADDER_H
#define ITE_LADDER_H

#include "ite_target_value_encoder.h"

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

class IteLadder : public IteTargetValueEncoder
{
public:
    IteLadder() = default;
    virtual ~IteLadder() = default;

    virtual void encode_target_value(const IteInstanceData &) override = 0;

    virtual void encode_labels(const IteInstanceData &) override = 0;

protected:
    std::unordered_map<std::vector<int>, int, VectorHash> target_value_aux_vars;

    int get_target_value_aux_var(const IteInstanceData &, std::vector<int> key, bool is_key_exist = false);

    void encode_ladder(const IteInstanceData &, const std::vector<int> ladder_vars, int width);
    void encode_window(const IteInstanceData &, const std::vector<int> window_vars, bool is_first_window, bool is_last_window);
    void connect_windows(const IteInstanceData &, const std::vector<int> first_window_vars, const std::vector<int> second_window_vars);
    void connect_ladder(const IteInstanceData &, const std::vector<int> first_ladder_vars, const std::vector<int> second_ladder_vars, int width);
};

#endif