#pragma once

#include "shader.h"

#include <vector>

class ShaderProgram
{
public:
	ShaderProgram();

	bool addShader(std::string& filePath, int shaderType);
	bool linkProgram();
	void useProgram();

private:
	GLuint id;
	std::vector<Shader> shaders;
};