#ifndef PROBLEM_TYPE_H
#define PROBLEM_TYPE_H

#include <iostream>

enum class ProblemType
{
    ABP,
    CyclicABP,

};

class ProblemTypeUtils
{
public:
    std::string GetProblemType(ProblemType type)
    {
        switch (type)
        {
        case ProblemType::ABP:
            return "Antibandwidth";
        case ProblemType::CyclicABP:
            return "Cyclic Antibandwdith";

        default:
            return "";
        }
    }
};

#endif