
#include "myShader.h"
#include "myMath.h"

#ifndef _mySdraw
#define _mySdraw 1

class mySdraw : public myShader
{
public:
	mySdraw();
	virtual bool init();
	void setWVP(const Matrix4f& WVP);

private:
	GLuint mWVPLocation;
};

#endif // !_mySdraw