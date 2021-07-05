#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderProgram.hpp"

float vertices[] = {
    -0.6f, -0.6f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};

int main(int argc, char **argv)
{
    if (!glfwInit())
    {
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(800, 600, "3d Game", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Could not create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl", GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl", GL_FRAGMENT_SHADER);

    program.link();

    //vertex buffer
    unsigned int VBO;
    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.4f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
