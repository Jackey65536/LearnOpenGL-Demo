#include <iostream>
// GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD。
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

namespace Ch04 {
    namespace BlendingDiscard {
        const unsigned int SCR_WIDTH = 1280;
        const unsigned int SCR_HEIGHT = 720;
        
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        void processInput(GLFWwindow *window);
        unsigned int loadTexture(char const * path);
        
        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
        float lastX = SCR_WIDTH / 2.0f;
        float lastY = SCR_HEIGHT / 2.0f;
        bool firstMouse = true;
        
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        
        int main(int argc, char * argv[]) {
            glfwInit(); // 初始化GLFW
            // 第一个参数代表选项的名称，我们可以从很多以GLFW_开头的枚举值中选择
            // 第二个参数接受一个整型，用来设置这个选项的值。
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            
            #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif
            
            // 创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被GLFW的其他函数频繁地用到。
            GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Blending Discard", NULL, NULL);
            if (!window) {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetScrollCallback(window, scroll_callback);
            
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            
            // GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }
            
            glEnable(GL_DEPTH_TEST);
            
            Shader shader("resources/shaders/blending.vs", "resources/shaders/blending.fs");

            float cubeVertices[] = {
                // positions          // texture Coords
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
            float planeVertices[] = {
                // positions          // texture Coords 
                5.0f, -0.51f,  5.0f,  2.0f, 0.0f,
                -5.0f, -0.51f,  5.0f,  0.0f, 0.0f,
                -5.0f, -0.51f, -5.0f,  0.0f, 2.0f,

                5.0f, -0.51f,  5.0f,  2.0f, 0.0f,
                -5.0f, -0.51f, -5.0f,  0.0f, 2.0f,
                5.0f, -0.51f, -5.0f,  2.0f, 2.0f
            };
            float transparentVertices[] = {
                // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
                0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
                0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
                1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

                0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
                1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
                1.0f,  0.5f,  0.0f,  1.0f,  0.0f
            };
            // cube VAO
            unsigned int cubeVAO, cubeVBO;
            glGenVertexArrays(1, &cubeVAO);
            glGenBuffers(1, &cubeVBO);
            glBindVertexArray(cubeVAO);
            glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            // plane VAO
            unsigned int planeVAO, planeVBO;
            glGenVertexArrays(1, &planeVAO);
            glGenBuffers(1, &planeVBO);
            glBindVertexArray(planeVAO);
            glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            // transparent VAO
            unsigned int transparentVAO, transparentVBO;
            glGenVertexArrays(1, &transparentVAO);
            glGenBuffers(1, &transparentVBO);
            glBindVertexArray(transparentVAO);
            glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), &transparentVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

            glBindVertexArray(0);

            //load textures
            unsigned int cubeTexture = loadTexture("resources/textures/marble.jpg");
            unsigned int floorTexture = loadTexture("resources/textures/metal.png");
            unsigned int transparentTexture = loadTexture("resources/textures/grass.png");

            std::vector<glm::vec3> vegetation
            {
                glm::vec3(-1.5f, 0.0f, -0.48f),
                glm::vec3( 1.5f, 0.0f, 0.51f),
                glm::vec3( 0.0f, 0.0f, 0.7f),
                glm::vec3(-0.3f, 0.0f, -2.3f),
                glm::vec3 (0.5f, 0.0f, -0.6f)
            };

            shader.use();
            shader.setInt("texture1", 0);
            
            // 渲染循环
            do {
                float currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;
                
                processInput(window);
                // 设置清空屏幕所用的颜色
                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                // 清空缓冲区，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                // draw objects
                shader.use();
                glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
                glm::mat4 view = camera.GetViewMatrix();
                glm::mat4 model = glm::mat4(1.0f);
                shader.setMat4("projection", projection);
                shader.setMat4("view", view);
                // cubes
                glBindVertexArray(cubeVAO);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, cubeTexture);
                model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
                shader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
                shader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                // floor
                glBindVertexArray(planeVAO);
                glBindTexture(GL_TEXTURE_2D, floorTexture);
                model = glm::mat4(1.0f);
                shader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // vegetation
                glBindVertexArray(transparentVAO);
                glBindTexture(GL_TEXTURE_2D, transparentTexture);
                for (GLuint i = 0; i < vegetation.size(); i++)
                {
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, vegetation[i]);
                    shader.setMat4("model", model);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                }
                
                
                // 交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
                glfwSwapBuffers(window);
                // 检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
                glfwPollEvents();
            } while (!glfwWindowShouldClose(window));// 检查一次GLFW是否被要求退出，如果是的话该函数返回true
            
            glDeleteVertexArrays(1, &cubeVAO);
            glDeleteVertexArrays(1, &planeVAO);
            glDeleteVertexArrays(1, &transparentVAO);
            glDeleteBuffers(1, &cubeVBO);
            glDeleteBuffers(1, &planeVBO);
            glDeleteBuffers(1, &transparentVBO);
            
            // 正确释放/删除之前的分配的所有资源
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
                camera.ProcessKeyboard(FORWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboard(BACKWARD, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboard(LEFT, deltaTime);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboard(RIGHT, deltaTime);
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
            float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
            
            lastX = xpos;
            lastY = ypos;
            
            camera.ProcessMouseMovement(xoffset, yoffset);
        }
        
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
        {
            camera.ProcessMouseScroll(yoffset);
        }
        
        unsigned int loadTexture(char const * path)
        {
            unsigned int textureID;
            glGenTextures(1, &textureID);
            
            int width, height, nrComponents;
            unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;
            
                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
                glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }
            
            return textureID;
        }
        
    }
}