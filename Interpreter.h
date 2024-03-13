#pragma once
#include <string>
#include <map>
#include <vector>
#include <strstream>
#include "Texture.h"
#include "RenderMath.h"

class SinopCommand
{
    public:
    virtual void DoOperation() = 0;
    virtual void Parse(std::vector<std::string> params){};
    void UpdateIdentifierValues();
    void ParseFloatExpression(std::string s, float* fp);
    std::vector<std::pair<float*,float*> > mNamedVariableLinks;
};

class SinopPushMatrixCommand : public SinopCommand
{
    public:
    void DoOperation() override;
};

class SinopPopMatrixCommand : public SinopCommand
{
    public:
    void DoOperation() override;
};

class SinopTranslateMatrixCommand : public SinopCommand
{
    public:    
    void DoOperation() override;
    void Parse(std::vector<std::string> parameters);

    private:
    float mX;
    float mY;
};

class SinopDrawImageCommand : public SinopCommand
{
    public:
    void DoOperation() override;
    void Parse(std::vector<std::string> parameters);

    private:
    CTexture* mTex = nullptr;
    Rect mSourceRect;
    Rect* mpSourceRect = nullptr;
    Color mBlendColor;
    bool mUsingBlendColor = false;
    static std::map<std::string, CTexture*> mTextures;
};

class SinopInterpreter
{
    public:
    void Parse(const std::string& txt);
    void Run();    

    private:
    std::vector<std::string> ReadCommand(std::strstream& strm);    
    std::vector<SinopCommand*> mCommands;
};