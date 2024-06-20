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
#include "FSData.h"

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
unsigned printResult = 0;
unsigned printVarTable = 0;
VarTable VARIABLES;
vector<Token> tokenList;
vector<RPNToken> tokensRPN;
vector<vector<RPNToken> > RPNList;

CFSData gFSData;

int main(int argc, char *argv[])
{
    // read and print the source program
    // auto src = readProgram("source3.sin");       // source2 and source3 moving png's
    auto src = readProgram("source-meters-only.sin"); // only metering altitude and ticks
    // auto src = readProgram("sourceTest.sin");
    // auto src = readProgram("sourceifthen.sin");
    // auto src = readProgram("sourcewhile.sin");

    // generate the program as a vector of RPN tokenlists
    VARIABLES.printVarTable();
    for (int i = 0; i < src.size(); i++)
    {
        if (src[i][0] == '#')
            continue;
        tokenList = makeTokenList(src[i], keywords, VARIABLES, reportlevel);
        RPNList.push_back(makeRPN(tokenList, reportlevel));
    };

    // exec(RPNList, VARIABLES);

    // return 0;

    gFSData.InitData();
    gFSData.CreateSocket();

    thread dialogThread(dialog);

    if (printResult + printVarTable == 0)
        CRenderer::InitSetStart(argc, argv, InitFunction, Renderfunction); // no rendering when testing

    dialogThread.join();

    return EXIT_SUCCESS;
}

void InitFunction()
{
    // this has to occur after inti of openGL, so cannot be in vartable.h
    int pingsSize = sizeof(VARIABLES.pings) / sizeof(VARIABLES.pings[0]);
    int texSize = sizeof(VARIABLES.tex) / sizeof(VARIABLES.tex[0]);
    if (pingsSize != texSize)
        cout << "ERROR: pings and text have different sizes" << endl;
    for (int i = 0; i < pingsSize ; i++)
        png_to_gl_texture(&VARIABLES.tex[i], (VARIABLES.pings[i]).c_str());
}

void Renderfunction()
{
    exec(RPNList, VARIABLES);
    // cout << "Flap: " << *gFlightSimulator.GetAddressOfNamedVariableFloat("FlapPosition") << endl;
}

void dialog()
{
    string ch = "";
    long unsigned int choice = 0;
    while (true)
    {
        cout << "\nchoice (1 to switch data source, 0 to exit) ==> ";
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
                gFSData.CloseSocket();
                return;
            case 1:
                VARIABLES.gUseXPData = 1 - (VARIABLES.gUseXPData > 0);
                cout << "you typed 1. we will switch to the other data source" << endl;

                break;
            default:
                cout << "you typed another interesting number. go on!" << endl;
                break;
            }
        }
        else if (ch == "r") // not used. reportLevel not propagated or so
        {
            reportlevel = 1 - (reportlevel > 0);
            cout << "reportlevel now is " << reportlevel << endl;
        }
        else
            cout << "no  number. retry" << endl;
    }
};