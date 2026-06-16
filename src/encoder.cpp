#include "global_data.h"
#include "encoder.h"
#include "searchers/ite_from_ub.h"
#include "searchers/ite_bfs.h"

#include <iostream>

Encoder::Encoder()
{
    searcher = get_searcher();
};

Encoder::~Encoder()
{
    delete searcher;
};

Searcher *Encoder::get_searcher()
{
    switch (GlobalData::search_strategy)
    {
    case SearchStrategy::iterate_from_ub:
        std::cout << "c [Main] Search strategy: Iterating from upper bound.\n";
        return new IteFromUB(GlobalData::target_value, GlobalData::lower_bound, GlobalData::upper_bound);
    case SearchStrategy::iterate_bfs:
        std::cout << "c [Main] Search strategy: Iterating Breath First Search.\n";
        return new IteBFS(GlobalData::target_value, GlobalData::lower_bound, GlobalData::upper_bound);

    default:
        std::cerr << "e [Main] Unrecognized search strategy " << static_cast<int>(GlobalData::search_strategy) << ".\n";
        exit(-1);
    }
}

void Encoder::encode_and_solve()
{
    std::cout << "c [Main] Encoding and solving for graph: " << GlobalData::g->graph_name << ".\n";

    searcher->encode_and_solve();
};

void Encoder::encode_and_print_dimacs()
{
    std::cout << "c [Main] Encoding and printing DIMACS for graph: " << GlobalData::g->graph_name << ".\n";

    searcher->encode_and_print_dimacs();
};
