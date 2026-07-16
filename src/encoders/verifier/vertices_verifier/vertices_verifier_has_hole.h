#ifndef VERTICES_VERIFIER_HAS_HOLE_H
#define VERTICES_VERIFIER_HAS_HOLE_H

#include "vertices_verifier.h"

class VerticesVerifierHasHole : public VerticesVerifier
{
public:
    VerticesVerifierHasHole() = default;
    ~VerticesVerifierHasHole() = default;

    bool verify_vertices(const std::vector<int> &label_assignment, const int span) override;
};

#endif