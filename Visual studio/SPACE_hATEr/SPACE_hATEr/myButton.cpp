#include "myButton.h"
myButton::myButton()
{
	mX = 0;
	mY = 0;
	mW = 0;
	mH = 0;
	mTexture[TEXTURE_NORMAL] = -1;
	mTexture[TEXTURE_HOVER] = -1;
	mTexture[TEXTURE_CLICK] = -1;
	mShown = false;
	mHover = false;
	mClick = false;
	mLock = false;
	mType = -1;
	

}

myButton::~myButton()
{
	mX = 0;
	mY = 0;
	mW = 0;
	mH = 0;
	mTexture[TEXTURE_NORMAL] = -1;
	mTexture[TEXTURE_HOVER] = -1;
	mTexture[TEXTURE_CLICK] = -1;
	mShown = false;
	mHover = false;
	mClick = false;
	mLock = false;
	mType = -1;
}

void myButton::lock()
{
	mLock = true;
}

void myButton::unlock()
{
	mLock = false;
}

bool myButton::isLock()
{
	return mLock;
}

void myButton::init(float x, float y, float w, float h, GLuint normal, GLuint hover, GLuint click, int type)
{
	mX = x;
	mY = y;
	mW = w;
	mH = h;
	mTexture[TEXTURE_NORMAL] = normal;
	mTexture[TEXTURE_HOVER] = hover;
	mTexture[TEXTURE_CLICK] = click;
	mType = type;
	

	mRect.initGui(x,y,w,h);
	
}

void myButton::render()
{
	if (!mShown)
		return;

	if (mType == MY_TYPE_TXT)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//printf("my type (%d) == (%d) MY_TYPE_TXT\n", mType, MY_TYPE_TXT);
	}
	
	glEnable(GL_TEXTURE_2D);


	if (mClick && !mLock)
		glBindTexture(GL_TEXTURE_2D, mTexture[TEXTURE_CLICK]);
	else 
		if (mHover && !mLock)
			glBindTexture(GL_TEXTURE_2D, mTexture[TEXTURE_HOVER]);
		else 
			glBindTexture(GL_TEXTURE_2D, mTexture[TEXTURE_NORMAL]);
		/*
	glBegin(GL_POLYGON);

	//bot - sx
	glTexCoord3f(0.0, 1.0, 0.0);
	glVertex3f(mX, mY, 0.0);
	//top - sx
	glTexCoord3f(0.0, 0.0, 0.0);
	glVertex3f(mX, mY + mH, 0.0);
	//top - dx
	glTexCoord3f(1.0, 0.0, 0.0);
	glVertex3f(mX+mW, mY+mH, 0.0);
	//bot - dx
	glTexCoord3f(1.0, 1.0, 0.0);
	glVertex3f(mX+mW, mY, 0.0);

	glEnd();/**/
	
	mRect.draw();/**/

	glDisable(GL_TEXTURE_2D);
	
	if (mType == MY_TYPE_TXT)
		glDisable(GL_BLEND);
}

void myButton::handleEvent(SDL_Event& e)
{
	//If an event was detected for this window
	//If mouse event happened
	if ((e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) && !mLock)
	{
		
		//Get mouse position
		float x1, y1, x, y;
		x1 = e.motion.x;
		y1 = e.motion.y;
		int w=1, h=1;
		
		SDL_GetWindowSize(SDL_GL_GetCurrentWindow(),&w,&h);

		x = (x1 * 1920) / w;
		y1 = h - y1;
		y = (y1 * 1080) / h;

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if (x < mX)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mX + mW)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mY)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mY + mH)
		{
			inside = false;
		}

		//Mouse is outside button
		if (inside)
		{
			//Set mouse over sprite
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				
				break;

			case SDL_MOUSEBUTTONDOWN:
				mClick = true;
				break;

			case SDL_MOUSEBUTTONUP:
				mClick = false;
				break;
			}
		}
		mHover = inside;
	}
}
void myButton::show()
{
	mShown = true;
}
void myButton::hide()
{
	mShown = false;
}
void myButton::resize(float w, float h)
{
	mW = w;
	mH = h;
}
int myButton::getWidth()
{
	return mW;
}
int myButton::getHeight()
{
	return mH;
}
bool myButton::isShown()
{
	return mShown;
}
bool myButton::isHover()
{
	return mHover;
}
bool myButton::isClick()
{
	return mClick;
}