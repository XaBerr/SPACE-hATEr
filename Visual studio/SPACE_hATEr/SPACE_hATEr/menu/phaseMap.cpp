#include "phaseMap.h"

phaseMap::phaseMap()
{
	mX = 1920.0;
	mY = 1080.0;
	mAlpha = 0;
	mdX = 0.0;
	mdX = 0.0;

}

phaseMap::~phaseMap()
{
	mX = 0;
	mY = 0;
	mAlpha = 0;
	mdX = 0.0;
	mdX = 0.0;
}

bool phaseMap::init()
{
	bool success =
	mMap.downLoadTexture(mX, mY) &&
	mShip.init();
	return success;
}

bool phaseMap::input(SDL_Event& e)
{
	if (!mShown)
		return true;

	if ((e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP))//e.type == SDL_MOUSEMOTION || 
	{

		//Get mouse position
		float  x, y;
		x = e.motion.x;
		y = e.motion.y;
		int w = 1, h = 1;

		SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &w, &h);

		x = (x * 1920) / w;
		y = h - y;
		y = (y * 1080) / h;

		switch (e.type)
		{
		case SDL_MOUSEMOTION:

			break;

		case SDL_MOUSEBUTTONDOWN:
			mdX = x - 960;//+= (x - 960);
			mdY = y - 540;//+= (y - 540);
			printf("mdX(%f) mdY(%f).\n", mdX, mdY);
			break;

		case SDL_MOUSEBUTTONUP:
			
			break;
		}

		

	}

	return true;
}

void phaseMap::fisica()
{
	if (!mShown)
		return;
	//printf("Fisica phaseMap.\n");
	//if ((abs(mNewX - ((int)mX%DIM_BLK_X)) < (VELOCITA*(1 / 60))) || (abs(mNewY - ((int)mY%DIM_BLK_Y)) < (VELOCITA*(1 / 60))))
	if (abs(mdX) > VELOCITA || abs(mdY) > VELOCITA)
	{
		printf("Fisica phaseMap.\n");
		makeMove(mdX, mdY);
	}

}

void phaseMap::grafica()
{
	if (!mShown)
		return;
	mMap.render();
	mShip.render();
}

void phaseMap::show()
{
	myElement::show();
}

void phaseMap::hide()
{
	myElement::hide();
}

void phaseMap::makeMove(float x, float y)
{
	mAlpha = atan((y) /(x));// alpha = arcsen (dY / dIpotenusa)
	mAlpha = abs(mAlpha);
	/*y -= 540;
	x -= 960;*/
	if (y >= 0 && x >= 0)
		mAlpha += 0 * (M_PI/2);
	if (y < 0 && x >= 0)
		mAlpha = 3 * (M_PI / 2) + ((M_PI / 2) - mAlpha);
	if (y < 0 && x < 0)
		mAlpha += 2 * (M_PI / 2);
	if (y >= 0 && x < 0)
		mAlpha = 1 * (M_PI / 2) + ((M_PI / 2) - mAlpha);
	//printf("dy(%f) dx(%f)\n",  y, x);
	
	//printf("mX(%f) mY(%f)\n",mX,mY);
	mX += VELOCITA * cos(mAlpha);
	mY += VELOCITA * sin(mAlpha);
	mdX -= VELOCITA * cos(mAlpha);
	mdY -= VELOCITA * sin(mAlpha);
	//printf("mX(%f) mY(%f) <--- +velocita'\n", mX, mY);

	move();
}

void phaseMap::move()
{
	mMap.move(mX,mY);
	mShip.move(mAlpha);
}