#include "global_data.h"
#include "mmsl_encoder.h"
#include "searchers/mmsl_incremental_from_ub.h"
#include "searchers/mmsl_iterate_from_ub.h"

#include <iostream>

MMSLEncoder::MMSLEncoder() {};

MMSLEncoder::~MMSLEncoder()
{
    if (mmsl_searcher != nullptr)
    {
        delete mmsl_searcher;
        mmsl_searcher = nullptr;
    }
};

void MMSLEncoder::setup_searcher()
{
    switch (GlobalData::search_strategy)
    {
    case SearchStrategy::iterate_from_ub:
        std::cout << "c [Main] Search strategy: Iterating from lower bound.\n";
        mmsl_searcher = new MMSLIterateFromUB();
        break;
    case SearchStrategy::incremental_from_ub:
        std::cout << "c [Main] Search strategy: Incremental from upper bound.\n";
        mmsl_searcher = new MMSLIncrementalFromUB();
        break;

    default:
        std::cerr << "e [Main] Unrecognized search strategy " << static_cast<int>(GlobalData::search_strategy) << ".\n";
        break;
    }
}

void MMSLEncoder::encode_and_solve()
{
    std::cout << "c [Main] Encoding and solving for graph: " << GlobalData::g->graph_name << ".\n";

    setup_searcher();

    mmsl_searcher->encode_and_solve();
};

void MMSLEncoder::encode_and_print_dimacs()
{
    std::cout << "c [Main] Encoding and printing DIMACS for graph: " << GlobalData::g->graph_name << ".\n";

    setup_searcher();

    mmsl_searcher->encode_and_print_dimacs();
};
