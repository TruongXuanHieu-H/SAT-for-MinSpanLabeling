#include "vertices_verifier_has_hole.h"

#include <assert.h>

bool VerticesVerifierHasHole::verify_vertices(const std::vector<int> &label_assignment, const int span)
{
    // Always return true due to no vertices constraints applied to has hole encoding.

    (void)label_assignment;
    (void)span;

    return true;
}