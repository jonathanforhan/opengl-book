#ifndef SHADER_HPP
#define SHADER_HPP

#include<glad/glad.h>

#include<string>
#include<vector>

class Shader {
public:
    uint32_t ID;

    Shader* addShader(const char* path, GLuint type);
    void createProgram(); 
    void use() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    void cleanup() const { glDeleteProgram(this->ID); }

private:
    static void checkCompileErrors(uint32_t shader, const std::string& type);
    static std::string getShaderName(GLuint type);

    std::vector<GLuint> mShaders{};
};

#endif
