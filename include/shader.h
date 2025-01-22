#include <glad/glad.h>   // This header has to be first for some reason -> remember this or else it crashess
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Our shader source code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;"
    "out vec3 ourColor;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"    //This is recieved from the vertex shader
    "void main(){\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n\0";

// Check functions are local for use by build_shader() and error handling
void checkVertex(unsigned int vertexShader);
void checkFragment(unsigned int fragmentShader);
void checkProgram(unsigned int shaderProgram);

unsigned int buildShader() {

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkVertex(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkFragment(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    // We now have the program and can delete the shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}



void checkVertex(unsigned int vertexShader) {
    //Checking for compile time errors in shader
    int successVertex;
    char infologVertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);

    if(!successVertex) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infologVertex);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infologVertex);
    }
}

void checkFragment(unsigned int fragmentShader) {
    int successFragment;
    char infologFragment[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);

    if(!successFragment) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infologFragment);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infologFragment);
    }
}

void checkProgram(unsigned int shaderProgram) {
    int successProgram;
    char infologProgram[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successProgram);

    if(!successProgram) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infologProgram);
        printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED");
    }
}