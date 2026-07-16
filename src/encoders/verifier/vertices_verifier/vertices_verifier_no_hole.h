#ifndef VERTICES_VERIFIER_NO_HOLE_H
#define VERTICES_VERIFIER_NO_HOLE_H

#include "vertices_verifier.h"

class VerticesVerifierNoHole : public VerticesVerifier
{
public:
    VerticesVerifierNoHole() = default;
    ~VerticesVerifierNoHole() = default;

    bool verify_vertices(const std::vector<int> &label_assignment, const int span) override;
};

#endif