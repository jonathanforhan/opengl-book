#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "window.hpp"
#include "cube.hpp"
#include "shader.hpp"
#include "texture.hpp"

struct WindowState windowState;

void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    windowState.width = width;
    windowState.height = height;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float& x, float& y, float& z) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        z -= 4;
    }
    else if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        z += 4;
    }
    else if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        y -= 4;
    }
    else if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        y += 4;
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowState.width, windowState.height, "opengl-book", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader shader;
    shader.addShader("../../shaders/test.vert", GL_VERTEX_SHADER)
          ->addShader("../../shaders/test.frag", GL_FRAGMENT_SHADER);
    shader.createProgram();

    Texture texture;
    texture.addTexture2D("../../assets/textures/crate.png", "tex1", GL_RGBA)
            ->addTexture2D("../../assets/textures/cpp.jpg", "tex2", GL_RGB);

    Cube cube(windowState, shader, texture);

    while(!glfwWindowShouldClose(window)) {
        float x{}, y{}, z{};
        processInput(window, x, y, z);

        double current = glfwGetTime();
        GLfloat color[] = {
            (float)sin(current) * 0.5f + 0.5f,
            (float)cos(current) * 0.5f + 0.5f,
            0.0f, 1.0f
        };
        glClearBufferfv(GL_COLOR, 0, color);
        glClear(GL_DEPTH_BUFFER_BIT);

        cube.render(x, y, z);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    shader.cleanup();
    cube.cleanup();

    glfwTerminate();
    return 0;
}
