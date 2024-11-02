#include<iostream>
#include<glad/glad.h>
#include<GLFW/GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell glfw we are using the core profile
	//so that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// creating a vertices array to pass on the coordinate vertices to draw an equilateral triangle
	// the square root calculation determines that all sides of the triangle are equal.
	GLfloat vertices[] =
	{
		-0.5f,-0.5f,-0.0f, //lower left
		0.5f,-0.5f,-0.0f, //lower right
		-0.5f,0.5f,-0.0f, //upper left
		-0.5f,0.5f,-0.0f, //upper left
		0.5f,0.5f,-0.0f, // upper right
		0.5f,-0.5f,-0.0f, //lower right
	};

	//Create a GLFWwindow object of 800 by 800 pixels, naming it 3d renderer
	GLFWwindow* window = glfwCreateWindow(800, 800, "3DRenderer", NULL, NULL);
	//error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Introduce the window in the current context
	glfwMakeContextCurrent(window);

	//load glad to configure Opengl

	gladLoadGL();

	// specify the viewport size
	glViewport(0, 0, 800, 800);

	// creating a vertex shader open gl unsigned int and assigning the vertex shader code to it.
	// compiling the shader by passing on the values
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//VBO stands for vertex buffer object (sends the vertices to the gpu)
	//VAO stands for vertex array object (connects the vertices)

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// specify the viewport color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//clean the back buffer and assign the new front buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	//main while loop
	while (!glfwWindowShouldClose(window))
	{
		//takes care of all the GLFW events
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}