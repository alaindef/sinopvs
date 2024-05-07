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

const static int render   = 1;
const static int rpn      = 2;
const static int gInt     = 4;

static int cf      = 
    rpn 
    // + gInt
    + render
    ; 
static int  reportlevel = 1;

    VarTable VARIABLES;
    vector<Token> tokenList;
    vector<RPNToken> tokensRPN;
    vector<vector<RPNToken>> program;

int main(int argc, char *argv[])
{
    vector<string> source0 = {
        "newA=Altitude",
        "newB=newA",
        "pushm()", 
        "trnsm(newB, Altitude)", 
        "drawm()"};                //20 22 23
    vector<string> source1 = {"pushm()    trnsm(200 , Altitude)   drawm()  " };
    vector<string> source3 = {"5 + b"};
    vector<string> source  = source0;
    if (cf & rpn) {
    for (int i = 0; i < source.size(); i++) {
        program.push_back(makeRPN(source[i], keywords, VARIABLES, reportlevel)); 
        calcandprint(program[i], VARIABLES, reportlevel);
        };
    } 
    
    if (cf & gInt)
    {
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

    if (cf & render)   CRenderer::InitSetStart(argc, argv, Renderfunction);

    dialogThread.join();
   
    return EXIT_SUCCESS;
}

void Renderfunction()
{
    // string sourceLine = "pushm() trnsm() drawm() pushm()";
    // vector<string> source0 = {"pushm()", "trnsm(Altitude, Altitude)", "drawm()", "pushm()"};
    // vector<string> source1 = {"pushm()    drawm() trnsm(200     , Altitude)       pushm() " };
    // vector<string> source  = source1;
    VarTable VARIABLES;
    vector<RPNToken> tokensRPN;
    if (cf & rpn){
    for (int i = 0; i < program.size(); i++) {
        // tokensRPN = makeRPN(source[i], keywords, VARIABLES, 0); 
        calcandprint(program[i], VARIABLES, true);
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