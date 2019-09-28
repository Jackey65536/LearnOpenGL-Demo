#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader.h>

namespace Ch01 {
    namespace ShadersClass {
        void framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
        
        int main(int argc, char * argv[]) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        
            GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders Class", NULL, NULL);
            if (!window) {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }
            
            Shader ourShader("resources/shaders/shaders_class.vs", "resources/shaders/shaders_class.fs");
            float vertices[] = {
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
               -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
                0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
            };
            
            unsigned int VAO, VBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);
            
            do {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                
                ourShader.use();
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
                
                glfwSwapBuffers(window);
                glfwPollEvents();
            } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));
            
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            
            glfwTerminate();
            return 0;
        }
    }
}
