#pragma once

#include "shader.h"

#include <vector>

class ShaderProgram
{
public:
	ShaderProgram();

	bool addShader(std::string filePath, int shaderType);
	bool linkProgram();
	bool reloadProgram();
	void useProgram();
	void deleteProgram();

private:
	GLuint id;
	std::vector<Shader> shaders;
};