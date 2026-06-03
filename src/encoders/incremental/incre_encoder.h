#ifndef INCRE_ENCODER_H
#define INCRE_ENCODER_H

class IncreInstanceData;

class IncreEncoder
{
public:
    IncreEncoder(IncreInstanceData *data);
    virtual ~IncreEncoder();

    virtual void encode_antibandwidth() = 0;

protected:
    IncreInstanceData *data;

    void encode_symmetry_break();

private:
    void encode_symmetry_break_first_node();
    void encode_symmetry_break_highest_degree_node();
    void encode_symmetry_break_lowest_degree_node();
};

#endif