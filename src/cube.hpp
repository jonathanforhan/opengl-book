#ifndef OPENGL_BOOK_SRC_CUBE_HPP
#define OPENGL_BOOK_SRC_CUBE_HPP

#include "window.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Cube {
public:
    explicit Cube(WindowState& pWindow, Shader  pShader, Texture pTexture);
    void cleanup();

    void rotate();
    void transform();

    void render(float x, float y, float z);

private:
    GLuint mVAO, mVBO;

    WindowState& mWindow;
    Shader mShader;
    Texture mTexture;

    struct {
        float x{};
        float y{};
        float z{};
    } angles;
};

#endif//OPENGL_BOOK_SRC_CUBE_HPP