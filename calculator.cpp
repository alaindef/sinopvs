#include <iostream>
#include "calculator.h"
#include <GL/gl.h>
#include <GL/freeglut.h>

float pushmatrix(float v1, float v2){
    return v1*v2*1000;
}

float calc(std::vector<RPNToken>& tokenlist, VarTable& vartabel){
    if (tokenlist.size() == 0) return 0.f;

    float res = 0;
    float v1 = 0;
    float v2 = 0;
    int i = 0;

    cursor--;
    if (cursor<0) cout << "\n\n !!! ERROR cursor !!!\n";
    RPNToken last = tokenlist[cursor];

    //remember that operands will be eaten in reverse order
    switch (last.opcode) {
    case OC::NUM:   res = last.value;                                                       break;
    case OC::VAR:   res = vartabel.getValue((int)last.value);                               break;
    case OC::MUL:   res = calc(tokenlist, vartabel) * calc(tokenlist, vartabel);            break;
    case OC::DIV:   v1  = calc(tokenlist, vartabel);  res = calc(tokenlist, vartabel)/v1;   break;
    case OC::ADD:   res = calc(tokenlist, vartabel) + calc(tokenlist, vartabel);            break;
    case OC::SUB:   v1  = calc(tokenlist, vartabel);  res = calc(tokenlist, vartabel) - v1; break;
    case OC::PAS:   res = calc(tokenlist, vartabel);                                        break;
    case OC::CHS:   res = -calc(tokenlist, vartabel);                                       break;
    case OC::LT:    res = calc(tokenlist, vartabel)   >  calc(tokenlist, vartabel);         break;
    case OC::LE:    res = calc(tokenlist, vartabel)   >= calc(tokenlist, vartabel);         break;
    case OC::GT:    res = calc(tokenlist, vartabel)   <  calc(tokenlist, vartabel);         break;
    case OC::GE:    res = calc(tokenlist, vartabel)   <= calc(tokenlist, vartabel);         break;
    case OC::EQ:    res = calc(tokenlist, vartabel)   == calc(tokenlist, vartabel);         break;
    case OC::NE:    res = calc(tokenlist, vartabel)   != calc(tokenlist, vartabel);         break;
    case OC::ASS:   res = calc(tokenlist, vartabel);
        vartabel.setVar(tokenlist[cursor-1].value, res); cursor--;                          break;
    case OC::COL:   v1  = calc(tokenlist, vartabel);  v2=calc(tokenlist, vartabel);
        res = calc(tokenlist, vartabel)?v2:v1;                                              break;
    case OC::pushm:
        for (i = 0; i < last.arity; i++) res += calc(tokenlist, vartabel);        // provisional
        // glPushMatrix();                                                                      
        break;
    case OC::popm:
        res = last.value * 2;
        break; // provisional                                                                     break;
    case OC::trnsm:
        break; // provisional                                                                  break;
    case OC::drawm:
        break; // provisional
    default:
        break;
    }
    return res;
}

void calcandprint(std::vector<RPNToken> &tokenlist, VarTable &vartabel, bool prt)
{
    cursor = tokenlist.size();
    float result = calc(tokenlist, vartabel);
    {
        std::cout << "EVALUATION RESULT ==> " << std::to_string(result) << std::endl;
    if (prt)
        vartabel.printVarTable();
        cout << "_______________________________________________________________________________" << std::endl;
    }
}
