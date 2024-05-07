#include <iostream>
#include <memory> 
#include "calculator.h"
#include "FlightSimulator.h"
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "Interpreter.h"
#include "Renderer.h"
#include <png.h>
#include "Texture.h"
#include "RenderMath.h"

extern CFlightSimulator gFlightSimulator;

static SinopDrawImageCommand *sdic = (new SinopDrawImageCommand);

float pushmatrix(float v1, float v2){
    return v1*v2*1000;
}

float calc(std::vector<RPNToken>& tokenlist, VarTable& vartabel, int & cursor){
    if (tokenlist.size() == 0) return 0.f;

    float res = 0;
    float v1 = 0;
    float v2 = 0;
    int i = 0;

    float* ptr;
    Rect recta = {0,0,256,196};
    CTexture adfTex;
    png_to_gl_texture(&adfTex, "spriteTest.png");

    cursor--;
    if (cursor<0) cout << "\n\n !!! ERROR cursor !!!\n";
    RPNToken last = tokenlist[cursor];
    //remember that operands will be eaten in reverse order
    switch (last.opcode) {
    case OC::NUM:   res = last.value;                                                       break;
    case OC::VAR:   res = vartabel.getValue((int)last.value);                               break;
    case OC::MUL:   res = calc(tokenlist, vartabel, cursor) * calc(tokenlist, vartabel, cursor);            break;
    case OC::DIV:   v1  = calc(tokenlist, vartabel, cursor);  res = calc(tokenlist, vartabel, cursor)/v1;   break;
    case OC::ADD:   res = calc(tokenlist, vartabel, cursor) + calc(tokenlist, vartabel, cursor);            break;
    case OC::SUB:   v1  = calc(tokenlist, vartabel, cursor);  res = calc(tokenlist, vartabel, cursor) - v1; break;
    case OC::PAS:   res = calc(tokenlist, vartabel, cursor);                                        break;
    case OC::CHS:   res = -calc(tokenlist, vartabel, cursor);                                       break;
    case OC::LT:    res = calc(tokenlist, vartabel, cursor)   >  calc(tokenlist, vartabel, cursor);         break;
    case OC::LE:    res = calc(tokenlist, vartabel, cursor)   >= calc(tokenlist, vartabel, cursor);         break;
    case OC::GT:    res = calc(tokenlist, vartabel, cursor)   <  calc(tokenlist, vartabel, cursor);         break;
    case OC::GE:    res = calc(tokenlist, vartabel, cursor)   <= calc(tokenlist, vartabel, cursor);         break;
    case OC::EQ:    res = calc(tokenlist, vartabel, cursor)   == calc(tokenlist, vartabel, cursor);         break;
    case OC::NE:    res = calc(tokenlist, vartabel, cursor)   != calc(tokenlist, vartabel, cursor);         break;
    case OC::ASS:   res = calc(tokenlist, vartabel, cursor);
        vartabel.setVar(tokenlist[cursor-1].value, res); cursor--;                          break;
    case OC::COL:   v1  = calc(tokenlist, vartabel, cursor);  v2=calc(tokenlist, vartabel, cursor);
        res = calc(tokenlist, vartabel, cursor)?v2:v1;                                              break;
    case OC::pushm:
        glPushMatrix();
        break;
    case OC::popm:
        res = last.value * 2;
        break;
    case OC::trnsm:
        v1 = calc(tokenlist, vartabel, cursor);
        v2 = calc(tokenlist, vartabel, cursor);
        glTranslatef(v1, v2, 0);

        break;
    case OC::drawm:
        sdic->DoOperation();
        CRenderer::DrawImage(&adfTex, &recta, 0xFFFFFFFF);
        break;

    default:
        break;
    }
    return res;
}

void calcandprint(std::vector<RPNToken> &tokenlist, VarTable &vartabel, bool prt)
{
    int cursor = tokenlist.size();
    float result = calc(tokenlist, vartabel, cursor);
}






    // if (prt)
    // {
    //     vartabel.printVarTable();
    //     cout << "_______________________________________________________________________________" << std::endl;
    // }
