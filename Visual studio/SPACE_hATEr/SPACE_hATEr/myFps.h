#include "myTexture.h"
#include "rectangle.h"
#include <SDL.h>
#include <string>
#include <sstream>

#ifndef _myFps
#define _myFps 1

class myFps
{
	public:
		myFps();
		~myFps();
		bool init(SDL_Color color, TTF_Font *font, float x, float y, float w, float h);
		void start();
		void render();

	private:
		float mOld;
		float mNew;
		int mFps;
		SDL_Color mColor;
		TTF_Font *mFont;
		myTexture mTexture;
		float mX;
		float mY;
		float mW;
		float mH;
		int mStabilize;
		rectangle mRec;

};

#endif // !_myFps
