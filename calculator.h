#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <functional>
#include "rpngenerator.h"


    float calc(std::vector<RPNToken> &tokenlist, VarTable &vartabel);
    void calcandprint(std::vector<RPNToken> &tokenlist, VarTable& vartabel, bool printResult, bool printVartable);

#endif // CALCULATOR_H
