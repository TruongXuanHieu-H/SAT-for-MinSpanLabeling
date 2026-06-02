#include "global_data.h"
#include "encoder.h"
#include "searchers/incre_from_ub.h"
#include "searchers/ite_from_ub.h"

#include <iostream>

Encoder::Encoder() {};

Encoder::~Encoder()
{
    if (searcher != nullptr)
    {
        delete searcher;
        searcher = nullptr;
    }
};

void Encoder::setup_searcher()
{
    switch (GlobalData::search_strategy)
    {
    case SearchStrategy::iterate_from_ub:
        std::cout << "c [Main] Search strategy: Iterating from lower bound.\n";
        searcher = new IteFromUB();
        break;
    case SearchStrategy::incremental_from_ub:
        std::cout << "c [Main] Search strategy: Incremental from upper bound.\n";
        searcher = new IncreFromUB();
        break;

    default:
        std::cerr << "e [Main] Unrecognized search strategy " << static_cast<int>(GlobalData::search_strategy) << ".\n";
        break;
    }
}

void Encoder::encode_and_solve()
{
    std::cout << "c [Main] Encoding and solving for graph: " << GlobalData::g->graph_name << ".\n";

    setup_searcher();

    searcher->encode_and_solve();
};

void Encoder::encode_and_print_dimacs()
{
    std::cout << "c [Main] Encoding and printing DIMACS for graph: " << GlobalData::g->graph_name << ".\n";

    setup_searcher();

    searcher->encode_and_print_dimacs();
};
