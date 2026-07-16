#ifndef SPAN_VERIFIER_H
#define SPAN_VERIFIER_H

#include <vector>

class SpanVerifier
{
public:
    SpanVerifier() = default;
    ~SpanVerifier() = default;

    bool verify_span(const std::vector<int> &label_assignment, const int span);
};

#endif