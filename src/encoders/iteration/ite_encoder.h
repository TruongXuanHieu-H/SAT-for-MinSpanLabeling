#ifndef ITE_ENCODER_H
#define ITE_ENCODER_H

class IteInstanceData;

class IteEncoder
{
public:
    IteEncoder(IteInstanceData &instance_data);
    virtual ~IteEncoder();

    virtual void encode_antibandwidth() = 0;

protected:
    IteInstanceData &instance_data;

    void encode_symmetry_break();

private:
    void encode_symmetry_break_first_node();
    void encode_symmetry_break_highest_degree_node();
    void encode_symmetry_break_lowest_degree_node();
};

#endif // ITE_ENCODER_H