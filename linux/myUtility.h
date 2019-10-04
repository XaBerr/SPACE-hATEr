//include
/*#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "GL/freeglut.h"
#include <string>*/
//my include
//#include "myWindow.h"
#include "myTexture.h"
#include "myMusic.h"
#include "myButton.h"
#include "mySave.h"
#include "myConfig.h"
#include "myFps.h"
#include "menu\menuStart.h"
#include "menu\phaseMap.h"
#include <sstream>

#ifndef _myUtility
#define _myUtility 1

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

//include


#define PIXEL_DEPTH 32
//init
bool initGL();
bool initSDL();
bool initLauncher();
bool initGame();
bool loadMedia();

//main
void startGame();
void hideLauncher();
void hideGame();
void showGame();
void resize(int w, int h);
void update();
void close();
void showGame();
void provaMappa();

//main loop
bool handleEvent(SDL_Event& e);
bool enginePhysics();
bool engineMenu();
void engineGraphics();

//other stuff
void old();
bool isQuit();
void freeLauncher();

#endif // !_myUtility