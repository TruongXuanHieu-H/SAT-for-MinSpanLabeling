#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

enum class SearchStrategy
{
    iterate_from_ub,    // Search from upper bound iteratively
    incremental_from_ub // Search from upper bound incrementally by modifying the encoding

};

#endif // SEARCH_STRATEGY_H