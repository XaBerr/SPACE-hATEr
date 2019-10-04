#include "..\myTexture.h"
#include <SDL.h>
//#include <math>
#ifndef _myShip
#define _myShip 1


class myShip
{
	public:
		myShip();
		~myShip();
		void render();
		void move(float alpha);
		bool init();

	private:
		float spinShip;
		myTexture mShipTexture;

};
#endif // !_myShip
