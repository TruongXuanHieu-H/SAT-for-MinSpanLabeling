#include "ite_from_ub.h"
#include "../global_data.h"

#include <iostream>

IteFromUB::IteFromUB(GlobalData &data) : Iteration(data)
{
    label_search_order = create_label_search_order();
    std::cout << "c [Main] Search order:";
    for (const auto &width : label_search_order)
    {
        std::cout << " " << width;
    }
    std::cout << ".\n";
}

IteFromUB::~IteFromUB() {}

std::deque<int> IteFromUB::create_label_search_order()
{
    std::deque<int> order_result;
    for (int i = global_data.upper_bound; i >= global_data.lower_bound; i--)
    {
        order_result.push_back(i);
    }
    return order_result;
}