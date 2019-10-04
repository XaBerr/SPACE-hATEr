#include "SDL.h"
#include "../myButton.h"
#include "../myTexture.h"

#ifndef _myElement
#define _myElement 1

class myElement
{
	public:
		myElement();
		~myElement();
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


#endif // !_myElement
