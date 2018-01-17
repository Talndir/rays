#define GLEW_STATIC			// Linking GLEW statically, requires glew32s.dll

#include "..\header\shaderProgram.h"

#include <Windows.h>

const int GL_VERSION_MAJOR = 4;
const int GL_VERSION_MINOR = 4;

bool reloadShaders = false;

void showConsole();
void hideConsole();
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
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

	// Test triangle
	float vertices[] = {
		-0.5f,	-0.5f,	0.0f,
		0.5f,	-0.5f,	0.0f,
		0.0f,	0.5f,	0.0f
	};

	// Create shader program
	ShaderProgram program;
	std::string shaderDir = ".\\shader\\";
	program.addShader(shaderDir + "test_vert.glsl", GL_VERTEX_SHADER);
	program.addShader(shaderDir + "test_frag.glsl", GL_FRAGMENT_SHADER);
	program.linkProgram();

	// VBO
	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear screen
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Reload shaders if necessary
		if (reloadShaders)
		{
			program.reloadProgram();
			reloadShaders = false;
		}

		// Use shader program
		program.useProgram();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}

	// Delete buffers
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

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
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, 1);
			break;
		case GLFW_KEY_R:
			reloadShaders = true;
			break;
		}
	}
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