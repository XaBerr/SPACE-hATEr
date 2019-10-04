#include "SDL.h"
//#include "../myButton.h"
#include "../myTexture.h"
#include "../map/myMap.h"

#ifndef _myMode
#define _myMode 1

class myMode
{
public:
	myMode();
	~myMode();
	bool init();
	bool input(SDL_Event& e);
	void fisica();
	void grafica();
	void hide();
	void show();
	bool isShown();

protected:
	bool mShown;


};


#endif // !_myMode
