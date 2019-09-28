#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <learnopengl/shader.h>

namespace Ch01 {
    namespace Textures {
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
        
            GLFWwindow* window = glfwCreateWindow(800, 600, "Textures", NULL, NULL);
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
            
            Shader ourShader("resources/shaders/textures.vs", "resources/shaders/textures.fs");

            float vertices[] = {
                // positions          // colors           // texture coords
                 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
                 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
            };
            unsigned int indices[] = {
                0, 1, 3,
                1, 2, 3
            };
            unsigned int VAO, VBO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // 位置属性
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // 颜色属性
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            // 纹理坐标属性
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            unsigned int texture;
            // 首先输入要生成纹理的数量，然后把它们存储在第二个参数的unsigned int数组中
            glGenTextures(1, &texture);
            // 绑定当前纹理，让之后任何的纹理指令都可以配置当前绑定的纹理
            glBindTexture(GL_TEXTURE_2D, texture);

            // 设置纹理的环绕方式
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            // 设置纹理的过滤方式
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int width, height, nrChannels;
            /*
             param1: 图像文件的位置
             param2: 用来填充图像宽度
             param3: 用来填充图像高度
             param4: 用来填充图像的颜色通道
             */
            unsigned char* data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
            if (data)
            {
                /*
                 给当前绑定的纹理对象附加上纹理图像
                 param1: 指定了纹理目标。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理。
                 param2: 为纹理指定多级渐远纹理的级别，0：基本级别。
                 param3: 告诉OpenGL我们希望把纹理存储为何种格式。
                 param4: 设置纹理的宽度
                 param5: 设置纹理的高度
                 param6: 纹理边界宽度，应该总是0（历史遗留的问题）
                 param7: 源图格式
                 param8: 源图数据类型
                 param9: 图像数据
                 */
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                // 为当前绑定的纹理自动生成所有需要的多级渐远纹理
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "Failed to load texture" << std::endl;
            }
            // 释放图像内存
            stbi_image_free(data);
            
            do {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                
                glBindTexture(GL_TEXTURE_2D, texture);

                ourShader.use();
                glBindVertexArray(VAO);
                // 把纹理赋值给片段着色器的采样器
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                
                glfwSwapBuffers(window);
                glfwPollEvents();
            } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));
            
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            
            glfwTerminate();
            return 0;
        }
    }
}
