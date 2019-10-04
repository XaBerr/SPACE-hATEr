
#include "myShader.h"
#include "myMath.h"

#ifndef _mySlight
#define _mySlight 1

struct dLight
{
	Vector3f Color;
	float ambientIntensity;
};

class mySlight : public myShader
{
public:
	mySlight();
	virtual bool init();
	void setWVP(const Matrix4f& WVP);
	void setTextureUnit(unsigned int TextureUnit);
	void setDirectionalLight(const dLight& Light);

private:

	GLuint mWVPLocation;
	GLuint mSamplerLocation;
	GLuint mDirLightColorLocation;
	GLuint mDirLightAmbientIntensityLocation;
};

#endif // !_mySlight
