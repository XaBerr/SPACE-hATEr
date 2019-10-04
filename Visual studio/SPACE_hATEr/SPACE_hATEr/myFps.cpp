#include "myFps.h"

myFps::myFps()
{
	mOld = -1;
	mNew = -1;
	mColor = {0,0,0};
	mFont = NULL;
	mX = -1;
	mY = -1;
	mW = -1;
	mH = -1;
	mStabilize = 0;
	mFps = 0;
}
myFps::~myFps()
{
}
bool myFps::init(SDL_Color color, TTF_Font *font, float x, float y, float w, float h)
{
	mColor = color;
	mFont = font;
	mX = x;
	mY = y;
	mW = w;
	mH = h;
	mRec.initGui(x,y,w,h);
	return true;
}
void myFps::start()
{
	mOld = SDL_GetTicks();
	mStabilize = 0;
	mFps = 60;
}
void myFps::render()
{
	float fps = 0;
	mStabilize++;
	mNew = SDL_GetTicks();
	fps = 1000 / ( mNew - mOld );
	mOld = mNew;
	if (mStabilize >= 40)
	{
		mFps = (int)fps;
		mStabilize -= 40;
	}
	
	std::ostringstream ss;
	ss <<"FPS: "<< mFps;
	mTexture.loadTTF(ss.str(), mColor, mFont);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture.getID());

	mW = mTexture.getWidth() * 0.3;

	/*glBegin(GL_POLYGON);
	glTexCoord3f(0.0, 1.0, 0.0);
	glVertex3f(mX, mY, 0.0);

	glTexCoord3f(0.0, 0.0, 0.0);
	glVertex3f(mX, mY+mH, 0.0);

	glTexCoord3f(1.0, 0.0, 0.0);
	glVertex3f(mX+mW, mY+mH, 0.0);

	glTexCoord3f(1.0, 1.0, 0.0);
	glVertex3f(mX+mW, mY, 0.0);
	glEnd();*/
	mRec.draw();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	mTexture.free();
}