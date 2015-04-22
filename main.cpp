/*
 * main.cpp
 *
 *  Created on: 22 Apr 2015
 *      Author: nathan
 */

#define GLEW_STATIC
#include <GL/glew.h>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <iostream>


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //sets opengl version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //prevent legacy function
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //user cant resize window

    // Create a GLFWwindow
    GLFWwindow* window = glfwCreateWindow(800, 600, "Space Game", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if ( window == NULL)
    {
    	std::cout << "Failed to create GLFW window" << std::endl;
    	glfwTerminate();
    	return -1;
    }

    //initialize GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
    	std::cout << "Failed to initialize GLEW" << std::endl;
    	return -1;
    }
    //rendering window
    glViewport(0, 0, 800, 600);

    //loop
    while(!glfwWindowShouldClose(window))//checks whether to close
    {
    	glfwPollEvents(); //checks event triggers
    	glfwSwapBuffers(window); //swap color buffer
    }

    //clean on exit
    glfwTerminate();
    return 0;

}
