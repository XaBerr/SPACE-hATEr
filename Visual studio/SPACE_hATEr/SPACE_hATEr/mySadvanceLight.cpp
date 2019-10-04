#include "mySadvanceLight.h"


static const char* pVS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
layout (location = 0) in vec3 Position;                                             \n\
layout (location = 1) in vec2 TexCoord;                                             \n\
layout (location = 2) in vec3 Normal;                                               \n\
                                                                                    \n\
uniform mat4 gWVP;                                                                  \n\
uniform mat4 gWorld;                                                                \n\
                                                                                    \n\
out vec2 TexCoord0;                                                                 \n\
out vec3 Normal0;                                                                   \n\
out vec3 WorldPos0;                                                                 \n\
                                                                                    \n\
void main()                                                                         \n\
{                                                                                   \n\
    gl_Position = gWVP * vec4(Position, 1.0);                                       \n\
    TexCoord0   = TexCoord;                                                         \n\
    Normal0     = (gWorld * vec4(Normal, 0.0)).xyz;                                 \n\
    WorldPos0   = (gWorld * vec4(Position, 1.0)).xyz;                               \n\
}";

static const char* pFS = "                                                          \n\
#version 330                                                                        \n\
                                                                                    \n\
const int MAX_POINT_LIGHTS = 2;                                                     \n\
const int MAX_SPOT_LIGHTS = 2;                                                      \n\
                                                                                    \n\
in vec2 TexCoord0;                                                                  \n\
in vec3 Normal0;                                                                    \n\
in vec3 WorldPos0;                                                                  \n\
                                                                                    \n\
out vec4 FragColor;                                                                 \n\
                                                                                    \n\
struct BaseLight                                                                    \n\
{                                                                                   \n\
    vec3 Color;                                                                     \n\
    float AmbientIntensity;                                                         \n\
    float DiffuseIntensity;                                                         \n\
};                                                                                  \n\
                                                                                    \n\
struct DirectionalLight                                                             \n\
{                                                                                   \n\
    BaseLight Base;                                                                 \n\
    vec3 Direction;                                                                 \n\
};                                                                                  \n\
                                                                                    \n\
struct Attenuation                                                                  \n\
{                                                                                   \n\
    float Constant;                                                                 \n\
    float Linear;                                                                   \n\
    float Exp;                                                                      \n\
};                                                                                  \n\
                                                                                    \n\
struct PointLight                                                                           \n\
{                                                                                           \n\
    BaseLight Base;                                                                         \n\
    vec3 Position;                                                                          \n\
    Attenuation Atten;                                                                      \n\
};                                                                                          \n\
                                                                                            \n\
struct SpotLight                                                                            \n\
{                                                                                           \n\
    PointLight Base;                                                                        \n\
    vec3 Direction;                                                                         \n\
    float Cutoff;                                                                           \n\
};                                                                                          \n\
                                                                                            \n\
uniform int gNumPointLights;                                                                \n\
uniform int gNumSpotLights;                                                                 \n\
uniform DirectionalLight gDirectionalLight;                                                 \n\
uniform PointLight gPointLights[MAX_POINT_LIGHTS];                                          \n\
uniform SpotLight gSpotLights[MAX_SPOT_LIGHTS];                                             \n\
uniform sampler2D gSampler;                                                                 \n\
uniform vec3 gEyeWorldPos;                                                                  \n\
uniform float gMatSpecularIntensity;                                                        \n\
uniform float gSpecularPower;                                                               \n\
                                                                                            \n\
vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)                   \n\
{                                                                                           \n\
    vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.AmbientIntensity;                   \n\
    float DiffuseFactor = dot(Normal, -LightDirection);                                     \n\
                                                                                            \n\
    vec4 DiffuseColor  = vec4(0, 0, 0, 0);                                                  \n\
    vec4 SpecularColor = vec4(0, 0, 0, 0);                                                  \n\
                                                                                            \n\
    if (DiffuseFactor > 0) {                                                                \n\
        DiffuseColor = vec4(Light.Color, 1.0f) * Light.DiffuseIntensity * DiffuseFactor;    \n\
                                                                                            \n\
        vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos0);                             \n\
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));                     \n\
        float SpecularFactor = dot(VertexToEye, LightReflect);                              \n\
        SpecularFactor = pow(SpecularFactor, gSpecularPower);                               \n\
        if (SpecularFactor > 0) {                                                           \n\
            SpecularColor = vec4(Light.Color, 1.0f) *                                       \n\
                            gMatSpecularIntensity * SpecularFactor;                         \n\
        }                                                                                   \n\
    }                                                                                       \n\
                                                                                            \n\
    return (AmbientColor + DiffuseColor + SpecularColor);                                   \n\
}                                                                                           \n\
                                                                                            \n\
vec4 CalcDirectionalLight(vec3 Normal)                                                      \n\
{                                                                                           \n\
    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, Normal);  \n\
}                                                                                           \n\
                                                                                            \n\
vec4 CalcPointLight(PointLight l, vec3 Normal)                                              \n\
{                                                                                           \n\
    vec3 LightDirection = WorldPos0 - l.Position;                                           \n\
    float Distance = length(LightDirection);                                                \n\
    LightDirection = normalize(LightDirection);                                             \n\
                                                                                            \n\
    vec4 Color = CalcLightInternal(l.Base, LightDirection, Normal);                         \n\
    float Attenuation =  l.Atten.Constant +                                                 \n\
                         l.Atten.Linear * Distance +                                        \n\
                         l.Atten.Exp * Distance * Distance;                                 \n\
                                                                                            \n\
    return Color / Attenuation;                                                             \n\
}                                                                                           \n\
                                                                                            \n\
vec4 CalcSpotLight(SpotLight l, vec3 Normal)                                                \n\
{                                                                                           \n\
    vec3 LightToPixel = normalize(WorldPos0 - l.Base.Position);                             \n\
    float SpotFactor = dot(LightToPixel, l.Direction);                                      \n\
                                                                                            \n\
    if (SpotFactor > l.Cutoff) {                                                            \n\
        vec4 Color = CalcPointLight(l.Base, Normal);                                        \n\
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));                   \n\
    }                                                                                       \n\
    else {                                                                                  \n\
        return vec4(0,0,0,0);                                                               \n\
    }                                                                                       \n\
}                                                                                           \n\
                                                                                            \n\
void main()                                                                                 \n\
{                                                                                           \n\
    vec3 Normal = normalize(Normal0);                                                       \n\
    vec4 TotalLight = CalcDirectionalLight(Normal);                                         \n\
                                                                                            \n\
    for (int i = 0 ; i < gNumPointLights ; i++) {                                           \n\
        TotalLight += CalcPointLight(gPointLights[i], Normal);                              \n\
    }                                                                                       \n\
                                                                                            \n\
    for (int i = 0 ; i < gNumSpotLights ; i++) {                                            \n\
        TotalLight += CalcSpotLight(gSpotLights[i], Normal);                                \n\
    }                                                                                       \n\
                                                                                            \n\
    FragColor = texture2D(gSampler, TexCoord0.xy) * TotalLight;                             \n\
}";



mySadvanceLight::mySadvanceLight()
{   
}

bool mySadvanceLight::init()
{
    if (!myShader::init()) {
        return false;
    }

    if (!addShader(GL_VERTEX_SHADER, pVS)) {
        return false;
    }

    if (!addShader(GL_FRAGMENT_SHADER, pFS)) {
        return false;
    }

    if (!finalize()) {
        return false;
    }

	mWVPLocation = getUniformLocation("gWVP");
	mWorldMatrixLocation = getUniformLocation("gWorld");
	mSamplerLocation = getUniformLocation("gSampler");
	mEyeWorldPosLocation = getUniformLocation("gEyeWorldPos");
	mDirLightLocation.color = getUniformLocation("gDirectionalLight.Base.Color");
	mDirLightLocation.ambientIntensity = getUniformLocation("gDirectionalLight.Base.AmbientIntensity");
	mDirLightLocation.direction = getUniformLocation("gDirectionalLight.Direction");
	mDirLightLocation.diffuseIntensity = getUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
	mMatSpecularIntensityLocation = getUniformLocation("gMatSpecularIntensity");
	mMatSpecularPowerLocation = getUniformLocation("gSpecularPower");
	mNumPointLightsLocation = getUniformLocation("gNumPointLights");
	mNumSpotLightsLocation = getUniformLocation("gNumSpotLights");

    if (mDirLightLocation.ambientIntensity == INVALID_UNIFORM_LOCATION ||
        mWVPLocation == INVALID_UNIFORM_LOCATION ||
        mWorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
        mSamplerLocation == INVALID_UNIFORM_LOCATION ||
        mEyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
        mDirLightLocation.color == INVALID_UNIFORM_LOCATION ||
        mDirLightLocation.diffuseIntensity == INVALID_UNIFORM_LOCATION ||
        mDirLightLocation.direction == INVALID_UNIFORM_LOCATION ||
        mMatSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
        mMatSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
        mNumPointLightsLocation == INVALID_UNIFORM_LOCATION ||
        mNumSpotLightsLocation == INVALID_UNIFORM_LOCATION)
	{
        return false;
    }

    for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(mPointLightsLocation) ; i++)
	{
        char Name[128];
        memset(Name, 0, sizeof(Name));
        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
        mPointLightsLocation[i].color = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
        mPointLightsLocation[i].ambientIntensity = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
        mPointLightsLocation[i].position = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
        mPointLightsLocation[i].diffuseIntensity = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
        mPointLightsLocation[i].atten.constant = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
        mPointLightsLocation[i].atten.linear = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
        mPointLightsLocation[i].atten.exp = getUniformLocation(Name);

        if (mPointLightsLocation[i].color == INVALID_UNIFORM_LOCATION ||
            mPointLightsLocation[i].ambientIntensity == INVALID_UNIFORM_LOCATION ||
            mPointLightsLocation[i].position == INVALID_UNIFORM_LOCATION ||
            mPointLightsLocation[i].diffuseIntensity == INVALID_UNIFORM_LOCATION ||
            mPointLightsLocation[i].atten.constant == INVALID_UNIFORM_LOCATION ||
            mPointLightsLocation[i].atten.linear == INVALID_UNIFORM_LOCATION ||
            mPointLightsLocation[i].atten.exp == INVALID_UNIFORM_LOCATION)
		{
            return false;
        }
    }

    for (unsigned int i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(mSpotLightsLocation) ; i++)
	{
        char Name[128];
        memset(Name, 0, sizeof(Name));
        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.Color", i);
        mSpotLightsLocation[i].color = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.AmbientIntensity", i);
        mSpotLightsLocation[i].ambientIntensity = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Position", i);
        mSpotLightsLocation[i].position = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
        mSpotLightsLocation[i].direction = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
        mSpotLightsLocation[i].cutoff = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.DiffuseIntensity", i);
        mSpotLightsLocation[i].diffuseIntensity = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Constant", i);
        mSpotLightsLocation[i].atten.constant = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Linear", i);
        mSpotLightsLocation[i].atten.linear = getUniformLocation(Name);

        SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Exp", i);
        mSpotLightsLocation[i].atten.exp = getUniformLocation(Name);

        if (mSpotLightsLocation[i].color == INVALID_UNIFORM_LOCATION ||
            mSpotLightsLocation[i].ambientIntensity == INVALID_UNIFORM_LOCATION ||
            mSpotLightsLocation[i].position == INVALID_UNIFORM_LOCATION ||
            mSpotLightsLocation[i].direction == INVALID_UNIFORM_LOCATION ||
            mSpotLightsLocation[i].cutoff == INVALID_UNIFORM_LOCATION ||
            mSpotLightsLocation[i].diffuseIntensity == INVALID_UNIFORM_LOCATION ||
            mSpotLightsLocation[i].atten.constant == INVALID_UNIFORM_LOCATION ||
            mSpotLightsLocation[i].atten.linear == INVALID_UNIFORM_LOCATION ||
            mSpotLightsLocation[i].atten.exp == INVALID_UNIFORM_LOCATION)
		{
            return false;
        }
    }

    return true;
}

void mySadvanceLight::setWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(mWVPLocation, 1, GL_TRUE, (const GLfloat*)WVP.m);    
}


void mySadvanceLight::setWorldMatrix(const Matrix4f& WorldInverse)
{
    glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_TRUE, (const GLfloat*)WorldInverse.m);
}


void mySadvanceLight::setTextureUnit(unsigned int textureUnit)
{
    glUniform1i(mSamplerLocation, textureUnit);
}


void mySadvanceLight::setDirectionalLight(const directionalLight& light)
{
    glUniform3f(mDirLightLocation.color, light.color.x, light.color.y, light.color.z);
    glUniform1f(mDirLightLocation.ambientIntensity, light.ambientIntensity);
    Vector3f tDirection = light.direction;
    tDirection.normalize();
    glUniform3f(mDirLightLocation.direction, tDirection.x, tDirection.y, tDirection.z);
    glUniform1f(mDirLightLocation.diffuseIntensity, light.diffuseIntensity);
}

void mySadvanceLight::setEyeWorldPos(const Vector3f& eyeWorldPos)
{
    glUniform3f(mEyeWorldPosLocation, eyeWorldPos.x, eyeWorldPos.y, eyeWorldPos.z);
}

void mySadvanceLight::setMatSpecularIntensity(float intensity)
{
    glUniform1f(mMatSpecularIntensityLocation, intensity);
}

void mySadvanceLight::setMatSpecularPower(float power)
{
    glUniform1f(mMatSpecularPowerLocation, power);
}

void mySadvanceLight::setPointLights(unsigned int numLights, const pointLight* pLights)
{
    glUniform1i(mNumPointLightsLocation, numLights);
    
    for (unsigned int i = 0 ; i < numLights ; i++)
	{
        glUniform3f(mPointLightsLocation[i].color, pLights[i].color.x, pLights[i].color.y, pLights[i].color.z);
        glUniform1f(mPointLightsLocation[i].ambientIntensity, pLights[i].ambientIntensity);
        glUniform1f(mPointLightsLocation[i].diffuseIntensity, pLights[i].diffuseIntensity);
        glUniform3f(mPointLightsLocation[i].position, pLights[i].position.x, pLights[i].position.y, pLights[i].position.z);
        glUniform1f(mPointLightsLocation[i].atten.constant, pLights[i].attenuation.constant);
        glUniform1f(mPointLightsLocation[i].atten.linear, pLights[i].attenuation.linear);
		glUniform1f(mPointLightsLocation[i].atten.exp, pLights[i].attenuation.exp);
    }
}

void mySadvanceLight::setSpotLights(unsigned int numLights, const spotLight* pLights)
{
	glUniform1i(mNumSpotLightsLocation, numLights);

	for (unsigned int i = 0; i < numLights; i++)
	{
        glUniform3f(mSpotLightsLocation[i].color, pLights[i].color.x, pLights[i].color.y, pLights[i].color.z);
        glUniform1f(mSpotLightsLocation[i].ambientIntensity, pLights[i].ambientIntensity);
        glUniform1f(mSpotLightsLocation[i].diffuseIntensity, pLights[i].diffuseIntensity);
        glUniform3f(mSpotLightsLocation[i].position,  pLights[i].position.x, pLights[i].position.y, pLights[i].position.z);
        Vector3f tDirection = pLights[i].direction;
        tDirection.normalize();
        glUniform3f(mSpotLightsLocation[i].direction, tDirection.x, tDirection.y, tDirection.z);
        glUniform1f(mSpotLightsLocation[i].cutoff, cosf(ToRadian(pLights[i].cutoff)));
        glUniform1f(mSpotLightsLocation[i].atten.constant, pLights[i].attenuation.constant);
        glUniform1f(mSpotLightsLocation[i].atten.linear,   pLights[i].attenuation.linear);
        glUniform1f(mSpotLightsLocation[i].atten.exp,      pLights[i].attenuation.exp);
    }
}
