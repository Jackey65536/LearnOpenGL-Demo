#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

namespace Ch02 {
    namespace BasicLightingDiffuse {
        const unsigned int SCR_WIDTH = 800;
        const unsigned int SCR_HEIGHT = 600;
        
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        void processInput(GLFWwindow *window);

        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
        float lastX = SCR_WIDTH / 2.0f;
        float lastY = SCR_HEIGHT / 2.0f;
        bool firstMouse = true;

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        
        int main(int argc, char * argv[]) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
#ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        
            GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Basic Lighting Diffuse", NULL, NULL);
            if (!window) {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetScrollCallback(window, scroll_callback);
            
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }
            
            glEnable(GL_DEPTH_TEST);

            Shader lightingShader("resources/shaders/basic_lighting.vs", "resources/shaders/basic_lighting.fs");
            Shader lampShader("resources/shaders/lamp.vs", "resources/shaders/lamp.fs");

            // 顶点向量、法向量
            float vertices[] = {
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
            };
            // ----------------箱子----------------
            unsigned int cubeVAO, VBO;
            glGenVertexArrays(1, &cubeVAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(cubeVAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            // 顶点属性
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // 法向量属性
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // ----------------灯泡----------------
            unsigned int lightVAO;
            glGenVertexArrays(1, &lightVAO);
            glBindVertexArray(lightVAO);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            
            do {
                float currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                processInput(window);
                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                lightingShader.use();
                lightingShader.setVec3("lightPos", lightPos);
                lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
                lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

                glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
                glm::mat4 view = camera.GetViewMatrix();
                lightingShader.setMat4("projection", projection);
                lightingShader.setMat4("view", view);

                glm::mat4 model = glm::mat4(1.0f);
                lightingShader.setMat4("model", model);

                glBindVertexArray(cubeVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);

                // 灯泡
                lampShader.use();
                lampShader.setMat4("projection", projection);
                lampShader.setMat4("view", view);
                model = glm::mat4(1.0f);
                model = glm::translate(model, lightPos);
                model = glm::scale(model, glm::vec3(0.2f));
                lampShader.setMat4("model", model);

                glBindVertexArray(lightVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                
                glfwSwapBuffers(window);
                glfwPollEvents();
            } while (!glfwWindowShouldClose(window));
            
            glDeleteVertexArrays(1, &cubeVAO);
            glDeleteVertexArrays(1, &lightVAO);
            glDeleteBuffers(1, &VBO);
            
            glfwTerminate();
            return 0;
        }
        
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

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(FORWARD, deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(BACKWARD, deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(LEFT, deltaTime);
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(RIGHT, deltaTime);
            }
        }
        
        void mouse_callback(GLFWwindow* window, double xpos, double ypos)
        {
            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }
            
            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;

            lastX = xpos;
            lastY = ypos;

            camera.ProcessMouseMovement(xoffset, yoffset);
        }
        
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
        {
            camera.ProcessMouseScroll(yoffset);
        }
    }
}