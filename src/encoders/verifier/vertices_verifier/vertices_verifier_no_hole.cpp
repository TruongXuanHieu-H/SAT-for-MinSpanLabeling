#include "vertices_verifier_no_hole.h"

#include <assert.h>

bool VerticesVerifierNoHole::verify_vertices(const std::vector<int> &label_assignment, const int span)
{
    std::vector<bool> used(span + 1, false);

    for (int label : label_assignment)
    {
        assert(1 <= label && label <= span);
        used[label] = true;
    }

    for (int label = 1; label <= span; label++)
        if (!used[label])
            return false;

    return true;
}