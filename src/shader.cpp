#include"shader.hpp"

#include<fstream>
#include<sstream>
#include<iostream>

/* Public */
Shader* Shader::addShader(const char* path, GLuint type) {
    std::string shaderCode;

    std::ifstream f;
    f.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    std::string shaderName = getShaderName(type);

    std::stringstream ss;

    try {
        f.open(path);
        ss << f.rdbuf();
        f.close();
        shaderCode = ss.str();
    } catch(std::ifstream::failure& e) {
        std::cout << "ERROR::" << shaderName << "::SHADER::FILE_READ_FAILURE\n" <<  e.what() << std::endl;
    }

    const char* shaderCodeCStr = shaderCode.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCodeCStr, nullptr);
    glCompileShader(shader);
    checkCompileErrors(shader, shaderName);

    mShaders.push_back(shader);

    return this;
}

void Shader::createProgram() {
    this->ID = glCreateProgram();

    for(const auto& shader : mShaders) {
        glAttachShader(ID, shader);
    }

    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    for(const auto& shader : mShaders) {
        glDeleteShader(shader);
    }

    mShaders.clear();
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

/* Private */
void Shader::checkCompileErrors(GLuint shader, const std::string& type) {
    int success;
    char infoLog[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::" << type << "::SHADER_COMPILATION_FAILURE\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::" << type << "::PROGRAM_LINKING_FAILURE\n" << infoLog << std::endl;
        }
    }
}

std::string Shader::getShaderName(GLuint type) {
    switch(type) {
        case GL_VERTEX_SHADER:
            return "VERTEX";
        case GL_FRAGMENT_SHADER:
            return "FRAGMENT";
        case GL_TESS_CONTROL_SHADER:
            return "TESS_CONTROL";
        case GL_TESS_EVALUATION_SHADER:
            return "TESS_EVALUATION";
        case GL_GEOMETRY_SHADER:
            return "GEOMETRY_SHADER";
        default:
            throw std::runtime_error("ERROR::BAD_SHADER_TYPE\n");
    }
}
