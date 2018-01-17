#include "..\header\shaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

bool ShaderProgram::addShader(std::string & filePath, int shaderType)
{
	Shader s;
	bool result = s.createShader(filePath, shaderType);

	if (!result)
	{
		s.deleteShader();
		return false;
	}

	shaders.push_back(s);
	glAttachShader(s.getId(), shaderType);

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

	return true;
}

void ShaderProgram::useProgram()
{
	glUseProgram(this->id);
}
