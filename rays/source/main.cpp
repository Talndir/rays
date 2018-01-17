#define GLEW_STATIC			// Linking GLEW statically, requires glew32s.dll

#include "..\header\shaderProgram.h"

#include <Windows.h>

const int GL_VERSION_MAJOR = 4;
const int GL_VERSION_MINOR = 6;

void showConsole();
void hideConsole();
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
	showConsole();

	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialise GLFW" << std::endl;
		return -1;
	}

	// Set up GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create main window
	GLFWwindow* window;
	window = glfwCreateWindow(1280, 720, "Rays", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create OpenGL window" << std::endl;
		glfwTerminate();
		return -2;
	}

	// Set window to current
	glfwMakeContextCurrent(window);

	// Initialise GLEW, need experimental for some extensions
	glewExperimental = GL_TRUE;
	
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -3;
	}

	// Set up key input
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	glfwSetKeyCallback(window, keyCallback);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}

	// Destroy window
	std::cout << "Destroying main window" << std::endl;
	glfwDestroyWindow(window);

	std::cout << "Exiting program" << std::endl;
	GL_VERTEX_SHADER;
	return 0;
}

// Key callback function for GLFW
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

// Show console
void showConsole()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);
}

// Hide console
void hideConsole()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}