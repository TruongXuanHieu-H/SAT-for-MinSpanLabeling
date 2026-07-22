#ifndef VERIFIER_H
#define VERIFIER_H

#include "span_verifier/span_verifier.h"

#include "target_value_verifier/target_value_verifier_abp.h"
#include "target_value_verifier/target_value_verifier_cabp.h"

#include "vertices_verifier/vertices_verifier_amo_vertex.h"
#include "vertices_verifier/vertices_verifier_has_hole.h"
#include "vertices_verifier/vertices_verifier_no_hole.h"

#include "../../enum/vertices_mode.h"
#include "../../enum/problem_type.h"

#include <memory>

class Verifier
{
public:
    Verifier(VerticesMode, ProblemType);
    ~Verifier() = default;

    bool verify_span(const Graph &g, const int target_value, const std::vector<int> label_assignment, const int span);
    bool verify_target_value(const Graph &g, const int target_value, const std::vector<int> label_assignment, const int span);
    bool verify_vertices(const Graph &g, const int target_value, const std::vector<int> label_assignment, const int span);

private:
    std::unique_ptr<SpanVerifier> span_verifier;
    std::unique_ptr<TargetValueVerifier> target_value_verifier;
    std::unique_ptr<VerticesVerifier> vertices_verifier;
};

#endif