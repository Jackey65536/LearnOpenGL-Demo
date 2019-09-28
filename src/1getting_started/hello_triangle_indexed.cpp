#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Ch01 {
    namespace HelloTriangleIndexed {
        const char* vertexShaderSource = "#version 330 core\n"
        // location指定输入变量
        "layout (location = 0) in vec3 aPos;\n"
        "out vec4 vertexColor;\n"
        "void main(void)\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
        "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 vertexColor;\n"
        "void main(void)\n"
        "{\n"
        "   FragColor = vertexColor;\n"
        "}\0";
        
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
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
            
            GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
            if (!window) {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            
            // glad: load all OpenGL function pointers
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }
            
            // 顶点着色器
            unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
            /*
             param1:要编译的着色器对象
             param2:传递的源码字符串数量
             param3:顶点着色器真正的源码
             */
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);
            // 检查编译是否成功
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            
            // 片段着色器
            unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            
            // 链接顶点和片段着色器
            unsigned int shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            // 检查连接是否成功
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            // 用不着了，可以删除
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            
            float vertices[] = {
                0.5f, 0.5f, 0.0f,   // 右上角
                0.5f, -0.5f, 0.0f,  // 右下角
                -0.5f, -0.5f, 0.0f, // 左下角
                -0.5f, 0.5f, 0.0f   // 左上角
            };
            unsigned int indices[] = { // 注意索引从0开始!
                0, 1, 3, // 第一个三角形
                1, 2, 3  // 第二个三角形
            };
            unsigned int VBO, VAO, EBO;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            
            /*
             告诉OpenGL该如何解析顶点数据（应用到逐个顶点属性上）
             param1:指定我们要配置的顶点属性
             param2:指定顶点属性的大小。坐标是一个vec3，他由3个值组成，所以坐标的顶点属性大小是3
             param3:指定数据的类型
             param4:是否希望数据被标准化(Normalize)。
             param5:步长(Stride)，他告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，所以这里设置为3*sizeof(float)
             param6:表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组开头，所以这里是0。
             */
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            // 启用顶点属性，参数：顶点属性值
            glEnableVertexAttribArray(0);
            
            // 解绑
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            
            do {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                
                glUseProgram(shaderProgram);
                // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
                glBindVertexArray(VAO);
                /*
                 param1:指定了绘制模式
                 param2:绘制顶点数，这里填6，也就是说我们一共需要绘制6个顶点。
                 param3:索引类型
                 param4:指定EBO中的偏移量
                 */
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
