
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../shaders/shader.h"







/*
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexColor;\n"
"void main()\n"
"{\n"
" FragColor = vertexColor;\n"
"}\0";
*/







/*
const char* tfragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.3f, 0.1f, 0.8f, 1.0f);\n"
"}\0";
*/



/*
float vertices[] = {	// three vertices (3D position) for triangle
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};
*/


float vertices[] = {
	   // positions //     // colors //
	-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom left
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom right
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top
};


/*
float vertices[] = {
	// Left triangle
	-0.75f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f,   // top
	-0.25f, -0.5f, 0.0f,  // bottom right

	// Right triangle
	 0.25f, -0.5f, 0.0f,  // bottom left
	 0.5f,  0.5f, 0.0f,   // top
	 0.75f, -0.5f, 0.0f   // bottom right
};
*/


/*
float vertices[] = { // rectangle
	 0.5f,  0.5f, 0.0f, // top right
	 0.5f, -0.5f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f // top left
};
*/



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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	/*            FOR ELEMENT BUFFER OBJECT
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	*/






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

		

		ourShader.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//---glUseProgram(tshaderProgram);	// triangle 2 using second shader
		//---glBindVertexArray(VAO);
		//---glDrawArrays(GL_TRIANGLES, 3, 3);


		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();	// clear the resources once finished
	return 0;


}









