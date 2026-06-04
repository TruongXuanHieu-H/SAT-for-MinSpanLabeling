#ifndef ITE_ENCODER_H
#define ITE_ENCODER_H

class IteEncoder
{
public:
    IteEncoder();
    virtual ~IteEncoder();

    virtual void encode_antibandwidth() = 0;

    void encode_symmetry_break();

private:
    void encode_symmetry_break_first_node();
    void encode_symmetry_break_highest_degree_node();
    void encode_symmetry_break_lowest_degree_node();
};

#endif // ITE_ENCODER_H