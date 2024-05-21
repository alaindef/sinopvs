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

// control what parts will be executed
const static int render = 1;
const static int rpn = 2;
const static int gInt = 4;
// comment out what you do not want to see
static int cf =
    rpn
    // + gInt
    + render;
static int reportlevel = 0; // >0 means that tokengen and RPNgen output will be printed

// provisional globals
VarTable VARIABLES;
vector<Token> tokenList;
vector<RPNToken> tokensRPN;
vector<vector<RPNToken> > program;

int main(int argc, char *argv[])
{
    auto prog = readProgram("source.sin");
    std::cout << "PROGRAM:\n-------" << endl;
    for (const std::string &line : prog)
    {
        std::cout << line << std::endl;
    }
    // vector<string> prog = {"aha"};
    // runP(prog, VARIABLES, 0);

    // return 0;
    if (cf & rpn)
    {
        for (int i = 0; i < prog.size(); i++)
        {
            program.push_back(makeRPN(prog[i], keywords, VARIABLES, reportlevel));
            calcandprint(program[i], VARIABLES, reportlevel);
        };
    }

    if (cf & gInt)
    {  //removed
    }

    thread dialogThread(dialog);

    if (cf & render)
    {
        CRenderer::InitSetStart(argc, argv, Renderfunction);
    }

    dialogThread.join();

    return EXIT_SUCCESS;
}

void Renderfunction()
{
        for (int i = 0; i < sizeof(VARIABLES.pings); i++)
            png_to_gl_texture(&VARIABLES.tex[i], (VARIABLES.pings[i]).c_str());
        for (int i = 0; i < program.size(); i++)
        {
            calcandprint(program[i], VARIABLES, false);
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