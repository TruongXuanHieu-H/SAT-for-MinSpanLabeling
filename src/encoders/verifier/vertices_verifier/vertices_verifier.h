#ifndef VERTICES_VERIFIER_H
#define VERTICES_VERIFIER_H

#include <vector>

class VerticesVerifier
{
public:
    VerticesVerifier() = default;
    virtual ~VerticesVerifier() = default;

    virtual bool verify_vertices(const std::vector<int> &label_assignment, const int span) = 0;
};

#endif