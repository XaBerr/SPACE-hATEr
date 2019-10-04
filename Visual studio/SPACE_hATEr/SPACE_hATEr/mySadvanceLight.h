#include <limits.h>
#include <string.h>
#include "myShader.h"
#include "myMath.h"
#include "myDefUtil.h"


#ifndef _mySadvanceLight
#define _mySadvanceLight 1

#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF

struct baseLight
{
	Vector3f color;
	float ambientIntensity;
	float diffuseIntensity;

	baseLight()
	{
		color = Vector3f(0.0f, 0.0f, 0.0f);
		ambientIntensity = 0.0f;
		diffuseIntensity = 0.0f;
	}
};

struct directionalLight : public baseLight
{
	Vector3f direction;

	directionalLight()
	{
		direction = Vector3f(0.0f, 0.0f, 0.0f);
	}
};

struct pointLight : public baseLight
{
	Vector3f position;

	struct
	{
		float constant;
		float linear;
		float exp;
	} attenuation;

	pointLight()
	{
		position = Vector3f(0.0f, 0.0f, 0.0f);
		attenuation.constant = 1.0f;
		attenuation.linear = 0.0f;
		attenuation.exp = 0.0f;
	}
};

struct spotLight : public pointLight
{
	Vector3f direction;
	float cutoff;

	spotLight()
	{
		direction = Vector3f(0.0f, 0.0f, 0.0f);
		cutoff = 0.0f;
	}
};

class mySadvanceLight : public myShader
{
	public:

		static const unsigned int MAX_POINT_LIGHTS = 2;
		static const unsigned int MAX_SPOT_LIGHTS = 2;

		mySadvanceLight();

		virtual bool init();

		void setWVP(const Matrix4f& WVP);
		void setWorldMatrix(const Matrix4f& WVP);
		void setTextureUnit(unsigned int textureUnit);
		void setDirectionalLight(const directionalLight& light);
		void setPointLights(unsigned int numLights, const pointLight* pLights);
		void setSpotLights(unsigned int numLights, const spotLight* pLights);
		void setEyeWorldPos(const Vector3f& eyeWorldPos);
		void setMatSpecularIntensity(float intensity);
		void setMatSpecularPower(float power);

	private:

		GLuint mWVPLocation;
		GLuint mWorldMatrixLocation;
		GLuint mSamplerLocation;
		GLuint mEyeWorldPosLocation;
		GLuint mMatSpecularIntensityLocation;
		GLuint mMatSpecularPowerLocation;
		GLuint mNumPointLightsLocation;
		GLuint mNumSpotLightsLocation;

		struct
		{
			GLuint color;
			GLuint ambientIntensity;
			GLuint diffuseIntensity;
			GLuint direction;
		} mDirLightLocation;

		struct
		{
			GLuint color;
			GLuint ambientIntensity;
			GLuint diffuseIntensity;
			GLuint position;
			struct
			{
				GLuint constant;
				GLuint linear;
				GLuint exp;
			} atten;
		} mPointLightsLocation[MAX_POINT_LIGHTS];

		struct
		{
			GLuint color;
			GLuint ambientIntensity;
			GLuint diffuseIntensity;
			GLuint position;
			GLuint direction;
			GLuint cutoff;
			struct
			{
				GLuint constant;
				GLuint linear;
				GLuint exp;
			} atten;
		} mSpotLightsLocation[MAX_SPOT_LIGHTS];
};


#endif // !_mySadvanceLight
