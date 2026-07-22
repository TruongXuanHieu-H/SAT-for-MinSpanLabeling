#include "span_verifier.h"

#include <algorithm>
#include <assert.h>

bool SpanVerifier::verify_span(const std::vector<int> &label_assignment, const int span)
{
    assert(!label_assignment.empty());

    int max_label = *std::max_element(label_assignment.begin(), label_assignment.end());
    int min_label = *std::min_element(label_assignment.begin(), label_assignment.end());

    return max_label == span && min_label == 1;
}