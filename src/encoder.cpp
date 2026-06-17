#include "global_data.h"
#include "encoder.h"
#include "searchers/incre_from_ub.h"
#include "searchers/ite_from_ub.h"
#include "searchers/ite_bfs.h"

#include <iostream>

Encoder::Encoder(GlobalData &data) : global_data(data), searcher(get_searcher()) {}

std::unique_ptr<Searcher> Encoder::get_searcher()
{
    switch (global_data.search_strategy)
    {
    case SearchStrategy::incremental_from_ub:
        std::cout << "c [Main] Search strategy: Incremental from upper bound.\n";
        return std::make_unique<IncreFromUB>(global_data);
    case SearchStrategy::iterate_from_ub:
        std::cout << "c [Main] Search strategy: Iterating from upper bound.\n";
        return std::make_unique<IteFromUB>(global_data);
    case SearchStrategy::iterate_bfs:
        std::cout << "c [Main] Search strategy: Iterating Breadth First Search.\n";
        return std::make_unique<IteBFS>(global_data);

    default:
        throw std::runtime_error("Unrecognized search strategy: " + std::to_string(static_cast<int>(global_data.search_strategy)));
    }
}

void Encoder::encode_and_solve()
{
    std::cout << "c [Main] Encoding and solving for graph: " << global_data.g->graph_name << ".\n";

    searcher->encode_and_solve();
}

void Encoder::encode_and_print_dimacs()
{
    std::cout << "c [Main] Encoding and printing DIMACS for graph: " << global_data.g->graph_name << ".\n";

    searcher->encode_and_print_dimacs();
}
