#include <iostream>
#include <cmath>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//GLM maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//other includes
#include <shader.h>
#include <camera.h>


//function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

//Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

//camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];

//light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//delta time
GLfloat deltaTime = 0.0f; 	//Time between current frame and last frame
GLfloat lastFrame = 0.0f;	//Time of last frame

//main function
int main()
{
	//init GLFW
	glfwInit();
	//set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//create window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SPACE", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	//set callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//GLFW options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//set this to true
	glewExperimental = GL_TRUE;
	//init GLEW
	glewInit();

	//viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	//opengl options
	glEnable(GL_DEPTH_TEST);

	//build shaders
	Shader lightingShader("colors.vs", "colors.frag");
	Shader lampShader("lamp.vs", "lamp.frag");

	//set up vertex data
	GLfloat vertices[] = {
		        -0.5f, -0.5f, -0.5f,
		         0.5f, -0.5f, -0.5f,
		         0.5f,  0.5f, -0.5f,
		         0.5f,  0.5f, -0.5f,
		        -0.5f,  0.5f, -0.5f,
		        -0.5f, -0.5f, -0.5f,

		        -0.5f, -0.5f,  0.5f,
		         0.5f, -0.5f,  0.5f,
		         0.5f,  0.5f,  0.5f,
		         0.5f,  0.5f,  0.5f,
		        -0.5f,  0.5f,  0.5f,
		        -0.5f, -0.5f,  0.5f,

		        -0.5f,  0.5f,  0.5f,
		        -0.5f,  0.5f, -0.5f,
		        -0.5f, -0.5f, -0.5f,
		        -0.5f, -0.5f, -0.5f,
		        -0.5f, -0.5f,  0.5f,
		        -0.5f,  0.5f,  0.5f,

		         0.5f,  0.5f,  0.5f,
		         0.5f,  0.5f, -0.5f,
		         0.5f, -0.5f, -0.5f,
		         0.5f, -0.5f, -0.5f,
		         0.5f, -0.5f,  0.5f,
		         0.5f,  0.5f,  0.5f,

		        -0.5f, -0.5f, -0.5f,
		         0.5f, -0.5f, -0.5f,
		         0.5f, -0.5f,  0.5f,
		         0.5f, -0.5f,  0.5f,
		        -0.5f, -0.5f,  0.5f,
		        -0.5f, -0.5f, -0.5f,

		        -0.5f,  0.5f, -0.5f,
		         0.5f,  0.5f, -0.5f,
		         0.5f,  0.5f,  0.5f,
		         0.5f,  0.5f,  0.5f,
		        -0.5f,  0.5f,  0.5f,
		        -0.5f,  0.5f, -0.5f
	};
	//set VAO + VBO
	GLuint VBO, containerVAO;
	glGenVertexArrays(1, &containerVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(containerVAO);
	//pos attr
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//light's VAO
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	//bind to the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attrib
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		//Deltatime
		GLfloat currentFrame = glfwGetTime();
	    deltaTime = currentFrame - lastFrame;
	    lastFrame = currentFrame;

	    // Check for events
	    glfwPollEvents();
	    do_movement();

	    // Clear the colorbuffer
	    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// shader
		lightingShader.Use();
		GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
		GLint lightColorLoc  = glGetUniformLocation(lightingShader.Program, "lightColor");
		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColorLoc,  1.0f, 0.5f, 1.0f);

		//Camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc  = glGetUniformLocation(lightingShader.Program,  "view");
		GLint projLoc  = glGetUniformLocation(lightingShader.Program,  "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw the container
		glBindVertexArray(containerVAO);
		glm::mat4 model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//Draw the lamp object
		lampShader.Use();
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc  = glGetUniformLocation(lampShader.Program, "view");
		projLoc  = glGetUniformLocation(lampShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}



