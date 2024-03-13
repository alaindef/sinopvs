#pragma once
#include "RenderMath.h"
#include "Texture.h"
#include <functional>

class CRenderer
{
    public:
    static void Init(int argc, char *argv[]);
    static void Render();
    static void Reshape(GLsizei,GLsizei);

    static void DrawImage(CTexture* tex, Rect* sourcerect = nullptr, Color colorargb = 0xFFFFFFFF);
    static void StartRendering();
    static void SetRenderFunction(const std::function<void(void)>& f) { mRenderFunction = f;}

    private:
    static CTexture mTexture;
    static std::function<void(void)> mRenderFunction;
};