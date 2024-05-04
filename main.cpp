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
#include "Interpreter.h"
#include "FlightSimulator.h"

#include "utils.h"
#include "vartable.h"
#include "tokengenerator.h"
#include "rpngenerator.h"
#include "calculator.h"

using namespace std;

SinopInterpreter gInterpreter;
CFlightSimulator gFlightSimulator;

void Renderfunction();
void dialog();

int main(int argc, char *argv[])
{
    string text = "pushm";
    VarTable VARIABLES;
    vector<Token> tokenList;
    vector<RPNToken> tokensRPN;

    tokensRPN = makeRPN(text, keywords, VARIABLES, 0);
    calcandprint(tokensRPN, VARIABLES, 0);

    gInterpreter.Parse(R"(
        PushMatrix()        
        // Translate(Altitude, 200)
        Translate(200, Altitude)
        DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 255, 255, 255 )
        PushMatrix()
        Translate(128, 100)        
        // DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 0, 0, 255 )     
        // PopMatrix()
        // Translate(0, 200)
        // DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 255, 0, 0 )
        // PopMatrix()
    )");

    thread dialogThread(dialog);
    CRenderer::Init(argc, argv);

    CRenderer::SetRenderFunction(Renderfunction);
    CRenderer::StartRendering();

    dialogThread.join();
    return EXIT_SUCCESS;
}

void Renderfunction()
{
    gInterpreter.Run();
}

void dialog()
{
    string ch = "";
    long unsigned int choice = 0;
    while (true)
    {
        cout << "\nchoice ==> ";
        cin >> ch;
        cin.ignore();
        if (ch == "r") return;
            // cout << "you typed r" << endl;
        if (ch != "")
        {
            choice = stoi(ch);
            cout << "choice = " << choice << endl;
            if (choice == 2){
                gInterpreter.Parse(R"(
                    PushMatrix()        
                    // Translate(Altitude, 200)
                    Translate(200, Altitude)
                    DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 255, 255, 255 )
                    PushMatrix()
                    // Translate(128, 100)        
                    // DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 0, 0, 255 )     
                    // PopMatrix()
                    // Translate(0, 200)
                    // DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 255, 0, 0 )
                    // PopMatrix()
                )");
            }
            else if (choice == 0) 
                return;
        }
        else if (ch == "r")
            cout << "you typed r" << endl;
        else
            cout << "no  number. retry" << endl;
    }
};