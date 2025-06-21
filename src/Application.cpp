#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.3f, 0.1f, 0.8f, 1.0f);\n"
"}\0";


/*
float vertices[] = {	// three vertices (3D position) for triangle
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};
*/

float vertices[] = { // rectangle
	 0.5f,  0.5f, 0.0f, // top right
	 0.5f, -0.5f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f // top left
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
	
	

	unsigned int VBO;															// initialise an ID for the VBO buffer
	glGenBuffers(1, &VBO);														// generate the buffer -- parameters(n, buffers)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);											// bind the buffer with target GL_ARRAY_BUFFER and buffer VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// copy user-defined data into currently bound buffer, VBO is bound to GL_ARRAY_BUFFER

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	int success;		// integer to indicate success
	char infoLog[512];	// storage container for error message

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);	// check if successful with glGetShaderiv
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);	// check if successful with glGetShaderiv
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;	
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING::FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	// Used to change the colour of the window
		glClear(GL_COLOR_BUFFER_BIT);			// Clear the colour buffer 

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();	// clear the resources once finished
	return 0;


}









