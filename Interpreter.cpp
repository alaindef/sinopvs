#include "Interpreter.h"
#include <strstream>
#include "helperfunctions.h"
#include "Renderer.h"
#include "FlightSimulator.h"

using namespace std;

extern CFlightSimulator gFlightSimulator;

void SinopInterpreter::Parse(const std::string &txt)
{
    strstream strm;
    strm<<txt;
    while (strm.good())
    {
        auto vec = ReadCommand(strm);
        if (vec.size() >= 2 && vec[0] == "DrawImage") {
            mCommands.push_back(new SinopDrawImageCommand());
            mCommands.back()->Parse(vec);
        }
        else if (vec.size() >= 3 && vec[0] == "Translate") {
            mCommands.push_back(new SinopTranslateMatrixCommand());
            mCommands.back()->Parse(vec);
        }
        else if (vec[0] == "PushMatrix")
            mCommands.push_back(new SinopPushMatrixCommand());
        else if (vec[0] == "PopMatrix")
            mCommands.push_back(new SinopPopMatrixCommand());
    }
}

void SinopInterpreter::Run()
{    
    // run the operations of the script
    for (auto& cmd : mCommands)
    {
        cmd->UpdateIdentifierValues();
        cmd->DoOperation();
    }
}

std::vector<std::string> SinopInterpreter::ReadCommand(strstream& strm)
{
    std::vector<std::string> tokens;
    tokens.push_back("");
    char ch = '\0';
    // get function name
    strm>>ch;
    if (ch == '#') 
        while (ch != '\n') strm>>ch;
    while (strm.good() && ch != '(' ) {
        tokens.back().push_back(ch);
        strm>>ch;
    }
    // get parameters
    strm>>ch;
    while (strm.good() && ch != ')') {
        if (tokens.size() <= 1) tokens.push_back("");
        if (ch == ',') {
            tokens.push_back("");
            strm>>ch;
        }
        tokens.back().push_back(ch);
        strm>>ch;
    }
    for (auto& token : tokens) trim(token);
    return tokens;
}

void SinopDrawImageCommand::DoOperation()
{
    if (!mTex) return;
    CRenderer::DrawImage(mTex, mpSourceRect, mUsingBlendColor ? mBlendColor : 0xFFFFFFFF);
}

std::map<std::string, CTexture*> SinopDrawImageCommand::mTextures;
void SinopDrawImageCommand::Parse(std::vector<std::string> parameters)
{
    if (parameters.size() <= 1) return;
    // if new texture
    if (mTextures.find(parameters[1]) == mTextures.end())
    {
        if (mTex) delete mTex;
        mTex = new CTexture();
        png_to_gl_texture(mTex, parameters[1].c_str());
        mTextures[parameters[1]] = mTex;
    }
    else
        mTex = mTextures[parameters[1]];
    
    // sourcerect
    if (parameters.size() <= 5) return;
    {
        mSourceRect.left = atof(parameters[2].c_str());
        mSourceRect.top = atof(parameters[3].c_str());
        mSourceRect.right = atof(parameters[4].c_str());
        mSourceRect.bottom = atof(parameters[5].c_str());
        mpSourceRect = &mSourceRect;
    }

    // blendcolor
    if (parameters.size() <= 9) return;
    {
        uint32_t a = atoi(parameters[6].c_str());
        uint32_t r = atoi(parameters[7].c_str());
        uint32_t g = atoi(parameters[8].c_str());
        uint32_t b = atoi(parameters[9].c_str());
        mBlendColor = ((a<<24)&0xFF000000) | ((r<<16)&0xFF0000) | ((g<<8)&0xFF00) | (b&0xFF);
        mUsingBlendColor = true;
    }
}

void SinopPushMatrixCommand::DoOperation()
{
    glPushMatrix();
}

void SinopPopMatrixCommand::DoOperation()
{
    glPopMatrix();
}

void SinopTranslateMatrixCommand::DoOperation()
{
    glTranslatef(mX, mY, 0);
}

void SinopTranslateMatrixCommand::Parse(std::vector<std::string> parameters)
{
    if (parameters.size() < 3) return;
    ParseFloatExpression(parameters[1], &mX); // mX = atof(parameters[1].c_str());
    ParseFloatExpression(parameters[2], &mY);// mY = atof(parameters[2].c_str());
}

void SinopCommand::UpdateIdentifierValues()
{
    if (mNamedVariableLinks.size() > 0)
        int debug = 0;
    // update all the values of referenced identifiers
    for (auto& floatpair : mNamedVariableLinks){
        *(floatpair.first) = *(floatpair.second);
        int debug = 0;
    }
}

void SinopCommand::ParseFloatExpression(std::string s, float *fp)
{
    // if string contains a literal number
    if (IsNumeric(s)) {
        *fp = atof(s.c_str());
    }
    // else if the string is an identifier of a named variable
    else if (s.find_first_of("<>()+-*/?:") == std::string::npos){
        float* const ptr = gFlightSimulator.GetAddressOfNamedVariableFloat(s);
        mNamedVariableLinks.emplace_back(fp, ptr);
    }
    // else it is a math expression
    else{
        // to be done
    }
}