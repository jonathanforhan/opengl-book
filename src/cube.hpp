#ifndef OPENGL_BOOK_SRC_CUBE_HPP
#define OPENGL_BOOK_SRC_CUBE_HPP

#include "shader.hpp"

class Cube {
public:
    Cube(Shader pShader);

    void rotate();
    void tranform();

    void render();
    void cleanup();

private:
    GLuint mVAO;
    Shader mShader;
};

#endif//OPENGL_BOOK_SRC_CUBE_HPP