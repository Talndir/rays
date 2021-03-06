#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader();
	
	bool createShader(std::string filePath, int shaderType);
	bool reloadShader();
	GLuint getId();
	void deleteShader();

private:
	GLuint id;				// Shader id
	int shaderType;			// Type of shader
	std::string filePath;	// Path to shader
};