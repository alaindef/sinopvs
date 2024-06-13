#ifdef __APPLE__
#else
#include <GL/gl.h>
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <thread>
#include <png.h>
#include "Renderer.h"
#include "Texture.h"
#include "FlightSimulator.h"

#include "utils.h"
#include "vartable.h"
#include "tokengenerator.h"
#include "rpngenerator.h"
#include "calculator.h"
#include "runprogram.h"

using namespace std;
CFlightSimulator gFlightSimulator;

void InitFunction();
void Renderfunction();
void dialog();
static int reportlevel = 0; // >0 means that tokengen and RPNgen output will be printed

// provisional globals
VarTable VARIABLES;
vector<Token> tokenList;
vector<RPNToken> tokensRPN;
vector<vector<RPNToken> > RPNList;

int main(int argc, char *argv[])
{
    // read and print the source program
    auto src = readProgram("source.sin");
    // auto src = readProgram("sourceTest.sin");
    // auto src = readProgram("sourceifthen.sin");
    // auto src = readProgram("source3.sin");

    // generate the program as a vector of RPN tokenlists
    for (int i = 0; i < src.size(); i++)
    {
        if (src[i][0] == '#')
            continue;
        tokenList = makeTokenList(src[i], keywords, VARIABLES, reportlevel);
        RPNList.push_back(makeRPN(tokenList, reportlevel));
    };
    VARIABLES.printVarTable();

    // exec(RPNList, VARIABLES, false);
    // exec0(RPNList, VARIABLES);

    // return 0;

    thread dialogThread(dialog);

    CRenderer::InitSetStart(argc, argv, InitFunction, Renderfunction); // disabled for test !!!!!!!!!!!!!!!

    dialogThread.join();

    return EXIT_SUCCESS;
}

void InitFunction()
{
    // this has to occur after inti of openGL, so cannot be in vartable.h
    for (int i = 0; i < sizeof(VARIABLES.pings); i++)
        png_to_gl_texture(&VARIABLES.tex[i], (VARIABLES.pings[i]).c_str());
}

void Renderfunction()
{
    exec0(RPNList, VARIABLES);
}

void dialog()
{
    string ch = "";
    long unsigned int choice = 0;
    while (true)
    {
        cout << "\nchoice (0 to exit) ==> ";
        cin >> ch;
        cin.ignore();
        if (isNumeric(ch))
        // if (ch != "")
        {
            choice = stoi(ch);
            cout << "choice = " << choice << endl;
            switch (choice)
            {
            case 0:
                glutLeaveMainLoop();
                return;
            case 1:
                cout << "you typed 1. nice try" << endl;
                break;
            default:
                cout << "you typed another interesting number. go on!" << endl;
                break;
            }
        }
        else if (ch == "r")                                         // not used. reportLevel not propagated or so
        {
            reportlevel = 1 - (reportlevel > 0);
            cout << "reportlevel now is " << reportlevel << endl;
        }
        else
            cout << "no  number. retry" << endl;
    }
};