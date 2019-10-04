#include "myElement.h"
#include "../map/myMap.h"
#include "../map/myShip.h"

#ifndef _phaseMap
#define _phaseMap 1

#define VELOCITA 4.0

class phaseMap : myElement
{
	public:
		phaseMap();
		~phaseMap();
		bool init();
		bool input(SDL_Event& e);
		void fisica();
		void grafica();
		void show();
		void hide();
		void makeMove(float x, float y);
		void move();


	protected:
		myMap mMap;
		myShip mShip;
		float mX;
		float mY;
		float mAlpha;
		float mdX;
		float mdY;
		
};

#endif // !_phaseMap
