
#include "mySlight.h"

static const char* pVS = 
"																					\n\
#version 330                                                                        \n\
						                                                            \n\
layout (location = 0) in vec3 Position;                                             \n\
layout (location = 1) in vec2 TexCoord;                                             \n\
																					\n\
uniform mat4 gWVP;                                                                  \n\
																					\n\
out vec2 TexCoord0;                                                                 \n\
																					\n\
void main()                                                                         \n\
{                                                                                   \n\
	gl_Position = gWVP * vec4(Position, 1.0);                                       \n\
	TexCoord0 = TexCoord;                                                           \n\
}";

static const char* pFS =
"																					\n\
#version 330                                                                        \n\
                                                                                    \n\
in vec2 TexCoord0;                                                                  \n\
                                                                                    \n\
out vec4 FragColor;                                                                 \n\
                                                                                    \n\
struct DirectionalLight                                                             \n\
{                                                                                   \n\
    vec3 Color;                                                                     \n\
    float AmbientIntensity;                                                         \n\
};                                                                                  \n\
                                                                                    \n\
uniform DirectionalLight gDirectionalLight;                                         \n\
uniform sampler2D gSampler;                                                         \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    FragColor = texture2D(gSampler, TexCoord0.xy) *                                 \n\
				vec4(gDirectionalLight.Color, 1.0f) *                               \n\
				gDirectionalLight.AmbientIntensity;                                 \n\
}";

mySlight::mySlight()
{
}

bool mySlight::init()
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
	mSamplerLocation = getUniformLocation("gSampler");
	mDirLightColorLocation = getUniformLocation("gDirectionalLight.Color");
	mDirLightAmbientIntensityLocation = getUniformLocation("gDirectionalLight.AmbientIntensity");

	if (mDirLightAmbientIntensityLocation == 0xFFFFFFFF ||
		mWVPLocation == 0xFFFFFFFF ||
		mSamplerLocation == 0xFFFFFFFF ||
		mDirLightColorLocation == 0xFFFFFFFF)
	{
		return false;
	}

	return true;
}

void mySlight::setWVP(const Matrix4f& WVP)
{
	glUniformMatrix4fv(mWVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);
}


void mySlight::setTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(mSamplerLocation, TextureUnit);
}


void mySlight::setDirectionalLight(const dLight& Light)
{
	glUniform3f(mDirLightColorLocation, Light.Color.x, Light.Color.y, Light.Color.z);
	glUniform1f(mDirLightAmbientIntensityLocation, Light.ambientIntensity);
}