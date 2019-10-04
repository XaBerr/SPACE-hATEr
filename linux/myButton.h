#include "SDL.h"
#include <GL/freeglut.h>
#include <sstream>

#ifndef _myButton
#define _myButton 1

#define MY_TYPE_IMAGE 0
#define MY_TYPE_TXT   1

#define TEXTURE_NORMAL 0
#define TEXTURE_HOVER  1
#define TEXTURE_CLICK  2

class myButton
{
	public:
		myButton();
		~myButton();
		void init(float x, float y, float w, float h, GLuint normal, GLuint hover, GLuint click, int type);
		void handleEvent(SDL_Event& e);
		void render();
		void free();
		void show();
		void hide();
		void resize(float w, float h);
		int getWidth();
		int getHeight();
		bool isShown();
		bool isHover();
		bool isClick();
		void lock();
		void unlock();
		bool isLock();

	private:
		float mX;
		float mY;
		float mW;
		float mH;
		GLuint mTexture[3];
		bool mShown;
		bool mHover;
		bool mClick;
		int mType;
		bool mLock;
};


#endif // !_myButton