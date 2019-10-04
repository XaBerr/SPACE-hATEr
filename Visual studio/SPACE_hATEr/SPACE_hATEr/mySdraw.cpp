#include "mySdraw.h"

static const char* pVS =
"																					\n\
#version 330                                                                        \n\
						                                                            \n\
layout (location = 0) in vec3 Position;                                             \n\
//layout (location = 1) in vec2 TexCoord;                                             \n\
																					\n\
uniform mat4 gWVP;                                                                  \n\
																					\n\
//out vec2 TexCoord0;                                                                 \n\
																					\n\
void main()                                                                         \n\
{                                                                                   \n\
	gl_Position = gWVP * vec4(Position, 1.0);                                       \n\
	//TexCoord0 = TexCoord;                                                           \n\
}";

static const char* pFS =
"																					\n\
#version 330                                                                        \n\
                                                                                    \n\
                                                                                    \n\
                                                                                    \n\
//in vec2 TexCoord0;                                                                  \n\
                                                                                    \n\
out vec4 FragColor;                                                                 \n\
                                                                                    \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);                                           \n\
}";

mySdraw::mySdraw()
{
}

bool mySdraw::init()
{
	if (!myShader::init())
	{
		return false;
	}

	if (!addShader(GL_VERTEX_SHADER, pVS))
	{
		return false;
	}

	if (!addShader(GL_FRAGMENT_SHADER, pFS))
	{
		return false;
	}

	if (!finalize())
	{
		return false;
	}

	mWVPLocation = getUniformLocation("gWVP");
	
	if (mWVPLocation == 0xFFFFFFFF)
	{
		printf("> WVP non linkata.\n");
		return false;
	}

	
	
	
	return true;
}

void mySdraw::setWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(mWVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}
