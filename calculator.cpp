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

float calc(std::vector<RPNToken> &tokenlist, VarTable &vartabel, int &cursor)
{
    if (tokenlist.size() == 0)
        return 0.f;

    vector<float> stack;

    float res = 0;
    float param[9];
    float p[10]; // parameters of an operator
    float *ptr;

    cursor = 0;
    int pnr;
    int arit;

    Rect recta = {0, 0, 256, 196};
    CTexture adfTex;
    png_to_gl_texture(&adfTex, "spriteTest.png");

    RPNToken last;

    while (cursor < tokenlist.size())
    {
        last = tokenlist[cursor];

        arit = last.arity; // use arity to fill up params! or p[]
        for (pnr = arit; pnr > 0; pnr--)
        {
            p[pnr] = stack.back();
            stack.pop_back();
        }

        switch (last.opcode)
        {
        case OC::NUM:
            stack.push_back(last.value);
            break;
        case OC::VAR:
            stack.push_back(vartabel.getValue((int)last.value));
            break;
        case OC::MUL:
            res = p[1] * p[2];
            stack.push_back(res);
            break;
        case OC::DIV:
            res = p[1] / p[2];
            stack.push_back(res);
            break;
        case OC::ADD:
            res = p[1] + p[2];
            stack.push_back(res);
            break;
        case OC::SUB:
            res = p[1] - p[2];
            stack.push_back(res);
            break;
        case OC::PAS:
            res = p[1];
            stack.push_back(res);
            break;
        case OC::CHS:
            res = -p[1];
            stack.push_back(res);
            break;
        case OC::LT:
            res = p[1] < p[2];
            stack.push_back(res);
            break;
        case OC::LE:
            res = p[1] <= p[2];
            stack.push_back(res);
            break;
        case OC::GT:
            res = p[1] > p[2];
            stack.push_back(res);
            break;
        case OC::GE:
            res = p[1] >= p[2];
            stack.push_back(res);
            break;
        case OC::EQ:
            res = p[1] == p[2];
            stack.push_back(res);
            break;
        case OC::NE:
            res = p[1] != p[2];
            stack.push_back(res);
            break;
        case OC::ASS:
            vartabel.setVar(p[1], p[2]);
            break;
        case OC::COL:
            res = p[1] ? p[2] : p[3];
            stack.push_back(res);
            break;
        case OC::pushm:
            glPushMatrix();
            break;
        case OC::popm:
            break;
        case OC::trnsm:
            glTranslatef(p[1], p[2], 0);
            break;
        case OC::drawm:
            sdic->DoOperation();
            CRenderer::DrawImage(&adfTex, &recta, 0xFFFFFFFF);
            break;

        default:
            break;
        }
        cursor++;
    }
    return res;
}

void calcandprint(std::vector<RPNToken> &tokenlist, VarTable &vartabel, bool prt)
{
    int cursor = tokenlist.size();
    float result = calc(tokenlist, vartabel, cursor);
    if (prt)
    {
        cout << "result = " << result << endl;
        vartabel.printVarTable();
    }
}

// if (prt)
// {
//     vartabel.printVarTable();
//     cout << "_______________________________________________________________________________" << std::endl;
// }
