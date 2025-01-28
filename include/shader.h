#include <glad/glad.h>   // This header has to be first for some reason -> remember this or else it crashess
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Our shader source code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    //"layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    //"out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 transform;\n"
    "void main(){\n"
    "   gl_Position = transform * vec4(aPos, 1.0f);\n"
    //"   ourColor = aColor;\n"
    "   TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    //"in vec3 ourColor;\n"    //This is recieved from the vertex shader
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture1;\n"
    "uniform sampler2D texture2;\n"
    "void main(){\n"
    // "   FragColor = vec4(ourColor, 1.0);\n"
    "   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
    "}\n\0";


// Check functions are local for use by build_shader() and error handling
void checkVertex(unsigned int vertexShader);
void checkFragment(unsigned int fragmentShader);
void checkProgram(unsigned int shaderProgram);

unsigned int buildShader() {
    // Building vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkVertex(vertexShader);

    // Building fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkFragment(fragmentShader);

    // Compiling them into a single shader program
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


//Checking for compile time errors in shader
void checkVertex(unsigned int vertexShader) {
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