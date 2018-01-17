#include "..\header\shader.h"

Shader::Shader()
{
}

bool Shader::createShader(std::string & filePath, int shaderType)
{
	// Check shader type is valid
	if (!(shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER ||
		shaderType == GL_COMPUTE_SHADER))
	{
		std::cout << "Shader creation: " << shaderType <<
			" is not a valid shader type" << std::endl;

		return false;
	}

	this->shaderType = shaderType;

	// Open file
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string code = "";

	try
	{
		file.open(filePath);
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		code = ss.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Failed to read shader at location " << filePath
			<< std::endl;

		return false;
	}

	// Compile shader
	id = glCreateShader(shaderType);
	const char* codeArr = code.c_str();
	glShaderSource(id, 1, &codeArr, NULL);
	glCompileShader(id);

	// Check for errors
	int success;
	glGetProgramiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char log[512];
		glGetProgramInfoLog(id, 1024, NULL, log);
		std::cout << "Error compiling shader:\n" << log << std::endl;

		return false;
	}

	return true;
}

GLuint Shader::getId()
{
	return this->id;
}

void Shader::deleteShader()
{
	glDeleteShader(this->id);
}
