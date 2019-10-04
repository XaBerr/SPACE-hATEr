
#include "myShader.h"
#include "myMath.h"

#ifndef _mySlightLESS
#define _mySlightLESS 1

class mySlightLESS : public myShader
{
public:
	mySlightLESS();
	virtual bool init();
	void setWVP(const Matrix4f& WVP);

private:
	GLuint mWVPLocation;
	GLuint mSample;

};

#endif // !_mySlightLESS