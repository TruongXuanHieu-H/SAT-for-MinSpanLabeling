#ifndef VERTICES_VERIFIER_AMO_VERTEX_H
#define VERTICES_VERIFIER_AMO_VERTEX_H

#include "vertices_verifier.h"

class VerticesVerifierAMOVertex : public VerticesVerifier
{
public:
    VerticesVerifierAMOVertex() = default;
    ~VerticesVerifierAMOVertex() = default;

    bool verify_vertices(const std::vector<int> &label_assignment, const int span) override;
};

#endif