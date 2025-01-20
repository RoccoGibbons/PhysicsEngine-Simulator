#include <glad/glad.h>   // This header has to be first for some reason -> remember this or else it crashess
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

// Our shader source code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


// A fragment shader determines the colour
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


int main() {

    // Initialising glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    // Making the window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Physics Engine", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create windown\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // Initialise GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialise GLAD\n");
        return -1;
    }

    // Building and compiliing the shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Checking for compile time errors in shader
    int successVertex;
    char infologVertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);

    if(!successVertex) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infologVertex);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infologVertex);
    }

    // Same thing with the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int successFragment;
    char infologFragment[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);

    if(!successFragment) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infologFragment);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infologFragment);
    }

    // Linking shaders to a program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    int successProgram;
    char infologProgram[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &successProgram);

    if(!successProgram) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infologProgram);
        printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED");
    }


    // We now have the program and can delete the shaders
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Our triangle shape
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    // We make our VBO, then we generate a buffer, then we bind this buffer to the array buffer, then copies the vertex data from our triangle into the buffers memory
    unsigned int VBO, VAO;  //VBO stands for Vertex Buffer Objects
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Linking Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glUseProgram(shaderProgram);


    // Render loop
    while(!glfwWindowShouldClose(window)) {
        // Input
        process_input(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}


// Allows window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    // If esc is pressed window closes
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);  // Vs code says is an error but it compiles and works as intended????
    }
}
