#include "Shader.hpp"
#include <fstream>
#include <iostream>

lumi::system::Shader::Shader()
{
	m_shaderIDs.reserve(2);
	m_iProgramID = 0;
}

lumi::system::Shader::~Shader()
{
	m_shaderIDs.clear();
	m_iProgramID = 0;
}

void lumi::system::Shader::addShader(std::string shaderFile, unsigned int shaderType)
{
	GLuint shaderID;
	std::string fileContents, currentLine;
	std::fstream fileStream;
	fileStream.open(shaderFile);
	if (fileStream.is_open())
	{
		while (std::getline(fileStream, currentLine))
		{
			fileContents += currentLine + "\n";
		}
	}
	shaderID = glCreateShader(shaderType);
	const GLchar* const shaderSource = fileContents.c_str();
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

    int  success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		if (shaderType == GL_VERTEX_SHADER)
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		else if (shaderType == GL_FRAGMENT_SHADER)
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		else
			std::cout << "An error occurred in shader compliation with: " << infoLog << std::endl;
    }
	m_shaderIDs.push_back(shaderID);
}

void lumi::system::Shader::compileProgram()
{
	m_iProgramID = glCreateProgram();
	for(const auto& shader : m_shaderIDs)
	{
		glAttachShader(m_iProgramID, shader);
	}
	glLinkProgram(m_iProgramID);

	int  success;
	char infoLog[512];
	glGetProgramiv(m_iProgramID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(m_iProgramID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	for(const auto& shader : m_shaderIDs)
	{
		glDeleteShader(shader);
	}
	m_shaderIDs.clear();
}

void lumi::system::Shader::useProgram()
{
	glUseProgram(m_iProgramID);
}

void lumi::system::Shader::unuseProgram()
{
    glUseProgram(0);
}

GLint lumi::system::Shader::getUniformLocation(std::string uniformName)
{
	return glGetUniformLocation(m_iProgramID, uniformName.c_str());
}