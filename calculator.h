#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <functional>
#include "rpngenerator.h"


    void calcandprint(std::vector<RPNToken> &tokenlist, VarTable& vartabel, bool prt);

#endif // CALCULATOR_H
