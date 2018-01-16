#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>

class Shader
{
public:
	Shader(std::string filePath, int shaderType);
	~Shader();

	GLuint id;			// Shader id
	int shaderType;		// Type of shader
};