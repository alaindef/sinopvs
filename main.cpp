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

static const bool rpn = true;
static int  reportlevel = 1;

int main(int argc, char *argv[])
{

    vector<string> source0 = {"pushm()", "trnsm(200,100)", "drawm()", "pushm()", "trnsm(128, 100)"};
    vector<string> source1 = {"pushm() trnsm(200,100) drawm() pushm() trnsm(128, 100)" };
    vector<string> source2 = {"trnsm(200,100)"};
    vector<string> source  = source2;
    VarTable VARIABLES;
    vector<Token> tokenList;
    vector<RPNToken> tokensRPN;

    if (rpn){
    for (int i=0; i<source.size(); i++) {
        tokensRPN = makeRPN(source[i], keywords, VARIABLES, reportlevel); 
        calcandprint(tokensRPN, VARIABLES, reportlevel);
        };
    } else{

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
    }

    thread dialogThread(dialog);

    // CRenderer::InitSetStart(argc, argv, Renderfunction);

    dialogThread.join();
   
    return EXIT_SUCCESS;
}

void Renderfunction()
{
    // string sourceLine = "pushm() trnsm() drawm() pushm()";
    vector<string> source0 = {"pushm()", "trnsm(200,100)", "drawm()", "pushm()", "trnsm(128, 100)"};
    vector<string> source1 = {"pushm() trnsm(200,100) drawm() pushm() trnsm(128, 100)" };
    vector<string> source  = source0;
    VarTable VARIABLES;
    vector<RPNToken> tokensRPN;
    // if (rpn){
    if (false){
    for (int i=0; i<source.size(); i++) {
        tokensRPN = makeRPN(source[i], keywords, VARIABLES, 0); 
        calcandprint(tokensRPN, VARIABLES, reportlevel);
        };
    } else
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