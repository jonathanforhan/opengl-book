#ifndef OPENGL_BOOK_SRC_TEXTURE_HPP
#define OPENGL_BOOK_SRC_TEXTURE_HPP

#include "glad/glad.h"
#include <vector>
#include <string>

class Texture {
public:
    Texture* addTexture2D(const char* path, const std::string& pname, GLint channels);

    const std::vector<std::pair<std::string, GLuint>>& getTextures() {
        return mTextures;
    }
private:
    std::vector<std::pair<std::string, GLuint>> mTextures{};
};

#endif//OPENGL_BOOK_SRC_TEXTURE_HPP