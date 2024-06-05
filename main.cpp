#ifdef __APPLE__
#include <GLUT/glut.h>
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
        // RPNList.push_back(makeRPN(prog[i], keywords, VARIABLES, reportlevel));
        if (src[i][0] == '#') continue;
        tokenList = makeTokenList(src[i], keywords, VARIABLES, reportlevel);
        RPNList.push_back(makeRPN(tokenList, reportlevel));
    };
    // VARIABLES.printVarTable();

    exec(RPNList, VARIABLES, src, false);

    // return 0;

    thread dialogThread(dialog);
    
    CRenderer::InitSetStart(argc, argv, InitFunction, Renderfunction);                             // disabled for test !!!!!!!!!!!!!!!

    dialogThread.join();

    return EXIT_SUCCESS;
}

void InitFunction()
{
    for (int i = 0; i < sizeof(VARIABLES.pings); i++)
        png_to_gl_texture(&VARIABLES.tex[i], (VARIABLES.pings[i]).c_str());
}

void Renderfunction()
{
    for (int i = 0; i < RPNList.size(); i++)
    {
        calcandprint(RPNList[i], VARIABLES, false, false);
    };
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
        if (ch == "r")
            return;
        // cout << "you typed r" << endl;
        if (ch != "")
        {
            choice = stoi(ch);
            cout << "choice = " << choice << endl;
            if (choice == 0)
            {
                glutLeaveMainLoop();
                return;
            }
            else
                switch (choice)
                // bedoeling hiervan is om at runtime te wisselen van source, maar werkt nog nie goed.
                // waarschijnlijk moet ik daarvoor den boel beter opkuisen vooraleer een nieuwe source te beginnen
                {
                case 1:
                    cout << "111111111111" << endl;
                    break;
                case 2:
                    cout << "222222222222" << endl;
                    break;

                default:
                    break;
                }
        }
        else if (ch == "r")
            cout << "you typed r" << endl;
        else
            cout << "no  number. retry" << endl;
    }
};