#include "verifier.h"

Verifier::Verifier(VerticesMode v_mode, ProblemType p_type)
{
    switch (v_mode)
    {
    case VerticesMode::no_hole:
        vertices_verifier = std::make_unique<VerticesVerifierNoHole>();
        break;
    case VerticesMode::has_hole:
        vertices_verifier = std::make_unique<VerticesVerifierHasHole>();
        break;
    case VerticesMode::amo_vertex:
        vertices_verifier = std::make_unique<VerticesVerifierAMOVertex>();
        break;
    default:
        break;
    }

    switch (p_type)
    {
    case ProblemType::ABP:
        target_value_verifier = std::make_unique<TargetValueVerifierABP>();
        break;
    case ProblemType::CyclicABP:
        target_value_verifier = std::make_unique<TargetValueVerifierCABP>();
        break;

    default:
        break;
    }

    span_verifier = std::make_unique<SpanVerifier>();
}

bool Verifier::verify_result(const Graph &g, const int target_value, const std::vector<int> label_assignment, const int span)
{
    if (!target_value_verifier->verify_target_value(g, target_value, label_assignment))
        return false;

    if (!span_verifier->verify_span(label_assignment, span))
        return false;

    if (!vertices_verifier->verify_vertices(label_assignment, span))
        return false;

    return true;
}