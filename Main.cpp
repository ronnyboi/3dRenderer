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
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}