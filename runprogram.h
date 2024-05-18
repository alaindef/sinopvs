#pragma once
#ifndef RUNPROGRAM_H
#define RUNPROGRAM_H
#include <functional>
#include "rpngenerator.h"

vector<string> readProgram(std::string filename);
void runP(std::vector<std::string> &program, VarTable &vartabel, bool prt);

#endif // RUNPROGRAM_H
