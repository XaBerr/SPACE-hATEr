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
#include "myMesh.h"
#include "menu/menuStart.h"
#include "menu/phaseMap.h"
#include "myPipeline.h"
#include "myShader.h"
#include "mySlight.h"
#include "mySlightLESS.h"
#include "mySadvanceLight.h"
#include "mySdraw.h"
#include <sstream>

#ifndef _myUtility
#define _myUtility 1

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

//include


#define PIXEL_DEPTH 32
//init
bool initGLEW();
bool initGL();
bool initSDL();
bool initLauncher();
bool initGame();
bool loadMedia();
void initShader();

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
void old2();
void initOld2();
bool isQuit();
void freeLauncher();
void drawMesh();


#endif // !_myUtility