
#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../shaders/shader.h"
#include "stb/stb_image.h"
#include "camera.h"

#include <../Dependencies/GLM/glm.hpp>
#include <../Dependencies/GLM/gtc/matrix_transform.hpp>
#include <../Dependencies/GLM/gtc/type_ptr.hpp>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);



void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed: y ranges bottom to top
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}





float mixValue = 0.1f;
 
float verticesX[] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
-0.5f,  0.5f, -0.5f, 0.0f, 1.0f
};


float vertices[] = {
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
		-0.5f,  0.5f, -0.5f,
};













float texCoords[] = {
	0.0f, 0.0f, // lower-left corner
	1.0f, 0.0f, // lower-right corner
	0.5f, 1.0f	// top-center corner
};







unsigned int indices[] = { // note that we start from 0!
	0, 1, 3, // first triangle
	1, 2, 3 // second triangle
};




void framebuffer_size_callback(GLFWwindow* window, int width, int height)	// This function is used to dynamically change the viewPort as the user resizes the window
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)	// Function to detect key press (esc) which would close the window
{

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;


	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(5.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		mixValue += 0.01f;
		mixValue = std::clamp(mixValue, 0.0f, 1.0f); // UNCLAMP FOR FUN EFFECT
	}
	
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		mixValue -= 0.01f;
		mixValue = std::clamp(mixValue, 0.0f, 1.0f); // UNCLAMP FOR FUN EFFECT
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







int main(void)
{

	GLFWwindow* window;

	





	/* Initialise the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 600, "champagne's engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	// Load the OpenGL function pointer addresses - still don't fully undertand what the fuck this does
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	
	//Shader ourShader("shaders/coord.vs", "shaders/coord.fs");
	//Shader lightingShader("shaders/light.vs", "shaders/light.fs");
	Shader lightingShader("shaders/vertex/colors.vs", "shaders/fragment/colors.fs");
	Shader lightCubeShader("shaders/vertex/light_cube.vs", "shaders/fragment/light_cube.fs");
	

	unsigned int VBO; // initialise an ID for the VBO buffer
	unsigned int cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// bind the buffer with target GL_ARRAY_BUFFER and buffer VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// copy user-defined data into currently bound buffer, VBO is bound to GL_ARRAY_BUFFER

	glBindVertexArray(cubeVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// second, configure the light's VAO
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	//---------------------------------------------------------------------------------
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	
	
	
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		
		processInput(window);	/* 
								// Detect whether user presses esc ky to close window, 
								// do it before glClear, otherwise function will wait until 
								// window is cleared
								*/


		
		
		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);					// Used to change the colour of the window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear the colour buffer 

		

		//-------3D-------//


		// activate shaders
		lightingShader.use();
		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		// world transformations
		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		// render the cube
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// also draw the lamp/light object
		lightCubeShader.use();
		lightCubeShader.setMat4("projection", projection);
		lightCubeShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // smaller cube using glm::scale
		lightCubeShader.setMat4("model", model);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightCubeVAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();	// clear the resources once finished
	return 0;


}









