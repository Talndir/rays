#include "..\header\shaderProgram.h"

ShaderProgram::ShaderProgram()
{
	this->id = glCreateProgram();
}

bool ShaderProgram::addShader(std::string filePath, int shaderType)
{
	Shader s;
	bool result = s.createShader(filePath, shaderType);

	if (!result)
	{
		s.deleteShader();
		return false;
	}

	shaders.push_back(s);
	glAttachShader(this->id, s.getId());

	return true;
}

bool ShaderProgram::linkProgram()
{
	glLinkProgram(this->id);

	int success;
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);

	if (!success)
	{
		char log[512];
		glGetProgramInfoLog(this->id, 1024, NULL, log);
		std::cout << "Error linking shader program:\n" << log << std::endl;

		return false;
	}

	std::cout << "Linking shader program OK" << std::endl;
	return true;
}

bool ShaderProgram::reloadProgram()
{
	bool result = true;

	for (int i = 0; i < shaders.size(); ++i)
		result &= shaders.at(i).reloadShader();

	result &= this->linkProgram();

	return result;
}

void ShaderProgram::useProgram()
{
	glUseProgram(this->id);
}

void ShaderProgram::deleteProgram()
{
	for (int i = 0; i < shaders.size(); ++i)
		shaders.at(i).deleteShader();

	glDeleteProgram(this->id);
}
