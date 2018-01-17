#include "..\header\shader.h"

Shader::Shader()
{
}

bool Shader::createShader(std::string filePath, int shaderType)
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

		this->filePath = filePath;
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
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char log[1024];
		glGetShaderInfoLog(id, 1024, NULL, log);
		std::cout << "Error compiling shader at location " << filePath <<
			"\n" << log << std::endl;

		return false;
	}

	std::cout << "Shader compile at location " << filePath <<
		" OK" << std::endl;
	return true;
}

bool Shader::reloadShader()
{
	return createShader(this->filePath, this->shaderType);
}

GLuint Shader::getId()
{
	return this->id;
}

void Shader::deleteShader()
{
	glDeleteShader(this->id);
}
