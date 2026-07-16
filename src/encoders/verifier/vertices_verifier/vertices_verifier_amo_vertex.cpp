#include "vertices_verifier_amo_vertex.h"

#include <assert.h>

bool VerticesVerifierAMOVertex::verify_vertices(const std::vector<int> &label_assignment, const int span)
{
    (void)span;

    for (int i = 0; i < (int)label_assignment.size(); i++)
        for (int j = i + 1; j < (int)label_assignment.size(); j++)
            if (label_assignment[i] == label_assignment[j])
                return false;

    return true;
}