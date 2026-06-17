#ifndef INCRE_ENCODER_H
#define INCRE_ENCODER_H

class IncreInstanceData;

class IncreEncoder
{
public:
    IncreEncoder(IncreInstanceData &instance_data);
    virtual ~IncreEncoder();

    virtual void encode_min_makespan_labeling() = 0;

protected:
    IncreInstanceData &instance_data;

    void encode_symmetry_break();

private:
    void encode_symmetry_break_first_node();
    void encode_symmetry_break_highest_degree_node();
    void encode_symmetry_break_lowest_degree_node();
};

#endif