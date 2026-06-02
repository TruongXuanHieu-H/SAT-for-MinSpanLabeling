#include "ite_from_ub.h"
#include "../global_data.h"

#include <iostream>

IteFromUB::~IteFromUB() {}

std::deque<int> IteFromUB::create_search_order()
{
    std::deque<int> order_result;
    for (int i = upper_bound; i >= lower_bound; i--)
    {
        order_result.push_back(i);
    }
    return order_result;
}