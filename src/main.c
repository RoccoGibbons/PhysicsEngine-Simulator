#include <glad/glad.h>   // This header has to be first for some reason -> remember this or else it crashess
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include <stb_image.h>

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main() {

    // Initialising glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    

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

    glEnable(GL_DEPTH_TEST);

    unsigned int shaderProgram = buildShader();
    glUseProgram(shaderProgram);

    // Our rectangle shape (made of 2 triangles)
    // float vertices[] = {
    //     // Vertices         Colours           Texture coords
    //     0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    //     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    // };

    // unsigned int indices[] = {
    //     0, 1, 3,
    //     1, 2, 3,
    // };

    // float vertices[] = {
    //     // Vertices               Colours
    //     -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    //      0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
    //      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    // }; 

    // unsigned int indices[] = {
    //     0, 1, 2
    // };

    // float texCoords[] = {
    //     0.0f, 0.0f,
    //     1.0f, 0.0f,
    //     0.5f, 1.0f,
    // };

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // We make our VBO, then we generate a buffer, then we bind this buffer to the array buffer, then copies the vertex data from our triangle into the buffers memory
    unsigned int VBO, VAO, EBO;  //VBO stands for Vertex Buffer Objects

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // Position Attribute                            // stride length   offset 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Colour Attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    // glEnableVertexAttribArray(1);

    // Texture Attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Textures
    unsigned int texture1, texture2;

    // Tex 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);    // S, T, R = X, Y, Z
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture");
    }
    stbi_image_free(data);

    // Tex 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Failed to load texture");
    }

    stbi_image_free(data);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);


    // Render loop
    while(!glfwWindowShouldClose(window)) {
        // Input
        process_input(window);

        // Rendering
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClearColor(0.2745f, 0.2863f, 0.3098f, 1.0f);
        glClearColor(0.1882f, 0.1921f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        // float timeValue = glfwGetTime();
        // float greenValue =  (sin(timeValue) / 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        // Binding textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);    

        // Transformations

        // This is the first test, this translates a given vector one right and one up
        // vec4 vec = {1.0f, 0.0f, 0.0f, 1.0f};
        // mat4 trans;
        // glm_mat4_identity(trans);
        // glm_translate(trans, (vec3){1.0f, 1.0f, 0.0f});
        // glm_mat4_mulv(trans, vec, vec);
        // printf("%f, %f, %f\n", vec[0], vec[1], vec[2]);    // This checks if the transformation works, which it does!

        // mat4 trans;
        // glm_mat4_identity(trans);
        // // glm_translate(trans, (vec3){0.5f, -0.5f, 0.0f});
        // glm_rotate(trans, (float)glfwGetTime(), (vec3){0.0f, 0.0f, 1.0f});
        // // glm_scale(trans, (vec3){0.5, 0.5, 0.5});

    
        glUseProgram(shaderProgram);
        // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, trans[0]);

        mat4 model; 
        glm_mat4_identity(model);
        glm_rotate(model, (float)(glfwGetTime() * glm_rad(50.0f)), (vec3){0.5f, 1.0f, 0.0f});

        mat4 view;
        glm_mat4_identity(view);
        glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});

        mat4 projection;
        glm_mat4_identity(projection);
        glm_perspective(glm_rad(45.0f), 800.0f/ 600.0f, 0.1f, 100.0f, projection);

        int modelloc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelloc, 1, GL_FALSE, model[0]);

        int viewloc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewloc, 1, GL_FALSE, view[0]);

        int projectionloc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionloc, 1, GL_FALSE, projection[0]);


        glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

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
