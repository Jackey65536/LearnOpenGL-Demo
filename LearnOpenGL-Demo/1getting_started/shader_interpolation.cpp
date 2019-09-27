#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Ch01 {
   namespace ShadersInterpolation {
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

          GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders Interpolation", NULL, NULL);
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

          do {
              glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
              glClear(GL_COLOR_BUFFER_BIT);

              // Draw

              glfwSwapBuffers(window);
              glfwPollEvents();
          } while (!glfwWindowShouldClose(window));
          
          glfwTerminate();
          return 0;
        }
    }
}