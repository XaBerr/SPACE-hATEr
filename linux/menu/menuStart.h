#include "myElement.h"

#ifndef _menuStart
#define _menuStart 1

class menuStart : myElement
{
	public:
		menuStart();
		~menuStart();
		bool init();
		bool input(SDL_Event& e);
		void fisica();
		void grafica();
		int menu();
		void show();
		void hide();

	protected:
		TTF_Font *mFont;

		myButton mContinua;
		myTexture mContinuaTexture[3];

		myButton mNuova;
		myTexture mNuovaTexture[3];

		myButton mOpzioni;
		myTexture mOpzioniTexture[3];

		myButton mEsci;
		myTexture mEsciTexture[3];

		myTexture gear;
		float spinGear;
};
#endif // !_menuStart
