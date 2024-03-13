#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/freeglut.h>
#endif

#include <png.h>
#include "Renderer.h"
#include "Texture.h"
#include "Interpreter.h"
#include "FlightSimulator.h"

SinopInterpreter gInterpreter;
CFlightSimulator gFlightSimulator;

void Renderfunction();

int main(int argc, char *argv[])
{
    CRenderer::Init(argc, argv);
    gInterpreter.Parse(R"(
        PushMatrix()        
        Translate(Altitude, 200)
        DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 255, 255, 255 )
        PushMatrix()
        Translate(200, 0)        
        DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 0, 0, 255 )        
        PopMatrix()
        Translate(0, 200)
        DrawImage( spriteTest.png, 0, 0, 128, 128, 255, 255, 0, 0 )
        PopMatrix()
    )");

    CRenderer::SetRenderFunction(Renderfunction);
    CRenderer::StartRendering();

    return EXIT_SUCCESS;
}


void Renderfunction()
{
    gInterpreter.Run();
}