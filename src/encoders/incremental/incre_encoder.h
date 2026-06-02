#ifndef INCRE_ENCODER_H
#define INCRE_ENCODER_H

class IncreEncoder
{
public:
    IncreEncoder();
    virtual ~IncreEncoder();

    virtual void encode_antibandwidth() = 0;

    void encode_symmetry_break();

private:
    void encode_symmetry_break_first_node();
    void encode_symmetry_break_highest_degree_node();
    void encode_symmetry_break_lowest_degree_node();
};

#endif