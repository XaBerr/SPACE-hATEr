//include
#include "SDL.h"
#include <GL/freeglut.h>
#include <sstream>

#ifndef _myWindow
#define _myWindow 1

//variabili
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PIXEL_DEPTH 32
#define TOTAL_WINDOWS 3

class myWindow
{
public:

	myWindow();
	bool init();
	bool init(int flag);
	void handleEvent(SDL_Event& e);
	void focus();
	void render();
	void free();
	void show();
	void hide();
	void resize(int w, int h);
	int getWidth();
	int getHeight();
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isShown();

private:

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	int mWindowID;
	int mWidth;
	int mHeight;
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mShown;
};
#endif // !_myWindow