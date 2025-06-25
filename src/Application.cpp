
#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../shaders/shader.h"
#include "stb/stb_image.h"

#include <../Dependencies/GLM/glm.hpp>
#include <../Dependencies/GLM/gtc/matrix_transform.hpp>
#include <../Dependencies/GLM/gtc/type_ptr.hpp>




float mixValue = 0.1f;
 



float texCoords[] = {
	0.0f, 0.0f, // lower-left corner
	1.0f, 0.0f, // lower-right corner
	0.5f, 1.0f	// top-center corner
};

float vertices[] = {
		// positions // colors // texture coords
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	// top right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// bottom left
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f	// top left
};

float vertices2[] = { // zoomed texture
	// positions // colors // texture coords
 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.55f, 0.55f,	// top right
 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.55f, 0.45f,	// bottom right
-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.45f, 0.45f,	// bottom left
-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.45f, 0.55f	// top left
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

	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))	// Load the OpenGL function pointer addresses - still don't fully undertand what the fuck this does
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}
	
	Shader ourShader("shaders/default.vs", "shaders/default.fs");

	unsigned int VBO;															// initialise an ID for the VBO buffer
	glGenBuffers(1, &VBO);														// generate the buffer -- parameters(n, buffers)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);											// bind the buffer with target GL_ARRAY_BUFFER and buffer VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// copy user-defined data into currently bound buffer, VBO is bound to GL_ARRAY_BUFFER

	
	
	
	




	

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attributes
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	

	/*         //FOR ELEMENT BUFFER OBJECT
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	*/

	

	
	unsigned int texture1;
	unsigned int texture2;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// PREVIOUSLY GL_REPEAT INSTEAD OF CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		// PREVIOUSLY GL_LINEAR INSTEAD OF NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("res/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
	}
	else 
	{
		std::cout << "Failed to load texture1" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	

	data = stbi_load("res/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
	}
	else
	{
		std::cout << "Failed to load texture2" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);





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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// Used to change the colour of the window
		glClear(GL_COLOR_BUFFER_BIT);			// Clear the colour buffer 

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.use();
		glBindVertexArray(VAO);
		ourShader.setFloat("mixer", mixValue);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//---glUseProgram(tshaderProgram);	// triangle 2 using second shader
		//---glBindVertexArray(VAO);
		//---glDrawArrays(GL_TRIANGLES, 3, 3);


		
		
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();	// clear the resources once finished
	return 0;


}









