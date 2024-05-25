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
    // auto prog = readProgram("source.sin");
    auto prog = readProgram("sourceTest.sin");
    // auto prog = readProgram("source.sin");
    std::cout << "PROGRAM:\n-------" << endl;
    // for (const std::string &line : prog) std::cout << line << std::endl;
    for (int ln=0; ln<prog.size();ln++) std::cout << ln << " " << prog[ln] << std::endl;

    // runP(prog, VARIABLES, false);

    // generate the program as a vector of RPN tokenlists
    for (int i = 0; i < prog.size(); i++)
    {
        // RPNList.push_back(makeRPN(prog[i], keywords, VARIABLES, reportlevel));
        if (prog[i][0] == '#') continue;
        tokenList = makeTokenList(prog[i], keywords, VARIABLES, reportlevel);
        RPNList.push_back(makeRPN(tokenList, reportlevel));
    };

    int cursor=0;
    // script(RPNList[0], RPNList, cursor);
    // runP(RPNList);
    exec(RPNList, VARIABLES, false);
    return 0;

    thread dialogThread(dialog);

    // CRenderer::InitSetStart(argc, argv, Renderfunction);                             // disabled for test !!!!!!!!!!!!!!!

    dialogThread.join();

    return EXIT_SUCCESS;
}

void Renderfunction()
{
    for (int i = 0; i < sizeof(VARIABLES.pings); i++)
        png_to_gl_texture(&VARIABLES.tex[i], (VARIABLES.pings[i]).c_str());
    for (int i = 0; i < RPNList.size(); i++)
    {
        calcandprint(RPNList[i], VARIABLES, false);
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