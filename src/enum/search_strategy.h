#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

enum class SearchStrategy
{
    incremental_from_ub, // Search using BFS incrementaly
    iterate_from_ub,     // Search from upper bound iteratively
    iterate_bfs,         // Search using BFS iteratively (left to right)
    iterate_bfs_reverse  // Search using BFS iteratively but in reverse order (right to left)
};

#endif // SEARCH_STRATEGY_H