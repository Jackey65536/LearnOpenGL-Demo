#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(int argc, const char * argv[]) {
    GLFWwindow* window;
    if (!glfwInit()) {
        return -1;
    }
    window = glfwCreateWindow(800, 600, "OpenGL Base Project", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    if (!glewInit()) {
        return -1;
    }
    glfwMakeContextCurrent(window);
    do {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        {
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(0, 0.5);
            
            glColor3f(0.0, 1.0, 0.0);
            glVertex2f(-0.5, -0.5);
            
            glColor3f(0.0, 0.0, 1.0);
            glVertex2f(0.5, -0.5);
        }
        glEnd();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window));
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
