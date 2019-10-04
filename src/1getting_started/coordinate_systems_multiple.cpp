#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>

namespace Ch01 {
    namespace CoordinateSystemsMultiple {
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;
        float fov = 45.0f;
        float ratio = (float)SCR_WIDTH/(float)SCR_HEIGHT;
        float viewX = 0.0f;
        float viewY = 0.0f;
        float viewZ = -3.0f;
        void framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }
        
        void processInput(GLFWwindow* window)
        {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                glfwSetWindowShouldClose(window, true);
            }
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
                fov++;
                std::cout << "fov = " << fov << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                fov--;
                std::cout << "fov = " << fov << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                ratio += 0.01f;
                std::cout << "ratio = " << ratio << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                ratio -= 0.01;
                std::cout << "ratio = " << ratio << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                viewX += 0.1f;
                std::cout << "viewX = " << viewX << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                viewX -= 0.1;
                std::cout << "viewX = " << viewX << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                viewY += 0.1f;
                std::cout << "viewY = " << viewY << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                viewY -= 0.1;
                std::cout << "viewY = " << viewY << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
                viewZ += 0.1f;
                std::cout << "viewZ = " << viewZ << std::endl;
            }
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
                viewZ -= 0.1;
                std::cout << "viewZ = " << viewZ << std::endl;
            }
        }
        
        int main(int argc, char * argv[]) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        
            GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Coordinate Systems Multiple", NULL, NULL);
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
            
            // SetRC
            glEnable(GL_DEPTH_TEST);
            
            Shader ourShader("resources/shaders/coordinate_systems.vs", "resources/shaders/coordinate_systems.fs");
            
            // set up vertex data (and buffer(s)) and configure vertex attributes
            // ------------------------------------------------------------------
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
            // world space positions of our cubes
            glm::vec3 cubePositions[] = {
                glm::vec3( 0.0f,  0.0f,  0.0f),
                glm::vec3( 2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3( 2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f,  3.0f, -7.5f),
                glm::vec3( 1.3f, -2.0f, -2.5f),
                glm::vec3( 1.5f,  2.0f, -2.5f),
                glm::vec3( 1.5f,  0.2f, -1.5f),
                glm::vec3(-1.3f,  1.0f, -1.5f)
            };
            unsigned int VAO, VBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            
            glBindVertexArray(VAO);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            unsigned int texture1, texture2;
            glGenTextures(1, &texture1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            int width, height, nrChannels;
            stbi_set_flip_vertically_on_load(true);
            unsigned char* data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture container.jpg" << std::endl;
            }
            stbi_image_free(data);

            glGenTextures(1, &texture2);
            glBindTexture(GL_TEXTURE_2D, texture2);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture awesomeface" << std::endl;
            }
            stbi_image_free(data);
            
            ourShader.use();
            ourShader.setInt("texture1", 0);
            ourShader.setInt("texture2", 1);
            
            do {
                processInput(window);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                // Draw
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture1);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture2);

                ourShader.use();

                glm::mat4 view = glm::mat4(1.0f);
                glm::mat4 projection = glm::mat4(1.0f);
                projection = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);
                view = glm::translate(view, glm::vec3(viewX, viewY, viewZ));
                ourShader.setMat4("projection", projection);
                ourShader.setMat4("view", view);

                glBindVertexArray(VAO);
                for (unsigned int i = 0; i < 10; i++)
                {
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, cubePositions[i]);
                    float angle = 20.0f * i;
                    if (i%3 == 0) {
                        angle = 20.0f * (i+1) * glfwGetTime();
                    }
                    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.1f*(i+1), 0.1f*(i+1), 0.1f*(i+1)));
                    ourShader.setMat4("model", model);

                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
                
                glfwSwapBuffers(window);
                glfwPollEvents();
            } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));
            
            // clean
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            
            glfwTerminate();
            return 0;
        }
    }
}
