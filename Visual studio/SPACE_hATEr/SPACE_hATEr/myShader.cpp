#include "myShader.h"

myShader::myShader()
{
	mShaderProg = 0;
}

myShader::~myShader()
{
	for (ShaderObjList::iterator it = mShaderObjList.begin(); it != mShaderObjList.end(); it++)
	{
		glDeleteShader(*it);
	}

	if (mShaderProg != 0)
	{
		glDeleteProgram(mShaderProg);
		mShaderProg = 0;
	}
}

bool myShader::init()
{
	mShaderProg = glCreateProgram();

	if (mShaderProg == 0)
	{
		fprintf(stderr, "> Errore creazione programma shader.\n");
		return false;
	}

	return true;
}

bool myShader::addShader(GLenum ShaderType, const char* pShaderText)
{
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0)
	{
		fprintf(stderr, "> Errore creazione shader type %d.\n", ShaderType);
		return false;
	}

	mShaderObjList.push_back(ShaderObj);

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);

	glCompileShader(ShaderObj);

	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "> Errore compilazione shader type %d: '%s'.\n", ShaderType, InfoLog);
		return false;
	}

	glAttachShader(mShaderProg, ShaderObj);

	return true;
}

bool myShader::finalize()
{
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	glLinkProgram(mShaderProg);

	glGetProgramiv(mShaderProg, GL_LINK_STATUS, &Success);
	if (Success == 0)
	{
		glGetProgramInfoLog(mShaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "> Errore linking programma shader: '%s'.\n", ErrorLog);
		return false;
	}

	glValidateProgram(mShaderProg);
	glGetProgramiv(mShaderProg, GL_VALIDATE_STATUS, &Success);
	if (!Success)
	{
		glGetProgramInfoLog(mShaderProg, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "> Invalido programma shader: '%s'.\n", ErrorLog);
		return false;
	}

	for (ShaderObjList::iterator it = mShaderObjList.begin(); it != mShaderObjList.end(); it++)
	{
		glDeleteShader(*it);
	}

	mShaderObjList.clear();

	return true;
}

void myShader::enable()
{
	glUseProgram(mShaderProg);
}

GLint myShader::getUniformLocation(const char* pUniformName)
{
	GLint Location = glGetUniformLocation(mShaderProg, pUniformName);

	if (Location == 0xFFFFFFFF)
	{
		fprintf(stderr, "< Warning! Impossibile trovare la locazione della uniform '%s'\n", pUniformName);
	}

	return Location;
}