#include "myUtility.h"


//myWindow gameWindow;//Mia finestra di prova
//___________________variabili launcher
SDL_Window* lWindow;						//Window launcher
SDL_Renderer* lRenderer;					//Render launcher
SDL_Surface* loadSurface(std::string path);	//Percorso file immagine launcher
SDL_Surface* lScreenSurface = NULL;			//Superfice finestra launcher
SDL_Surface* lJPGSurface = NULL;			//Superfice Immagine launcher
//___________________varabili gioco
myConfig gConfig;
SDL_Window* gWindow;
SDL_GLContext gContext;
int gWindowID;
int gWidth;
int gHeight;
int gScreenMode;
bool gMouseFocus;
bool gKeyboardFocus;
bool gShown;
//___________________altre variabili
//myTexture prova;
myMusic suono;
TTF_Font *gFont = NULL;

menuStart gMenuStart;
phaseMap gGameMap;

int ElementShown;

myFps fps;


/*
typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALFARPROC)(int);
PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = 0;

void setVSync(int interval = 1)
{
	const char *extensions = glGetString(GL_EXTENSIONS);

	if (strstr(extensions, "WGL_EXT_swap_control") == 0)
		return; // Error: WGL_EXT_swap_control extension not supported on your computer.\n");
	else
	{
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");

		if (wglSwapIntervalEXT)
			wglSwapIntervalEXT(interval);
	}
}
*/

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	glViewport(0, 0, gWidth, gHeight );

	//Inizializzazione Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//in basso a sx dovrebbe esserci lo 0-0
	//va da 1 a 1920, non so se funziona bene...
	glOrtho(0, 1920, 0, 1080, 1, -1);

	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("> Errore GL_PROJECTION:\n%s\n", gluErrorString(error));
		success = false;
	}

	//diabilitare vsynch
	

	//Inizializzazione Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("> Errore GL_MODELVIEW:\n%s\n", gluErrorString(error));
		success = false;
	}

	//Inizializzazione colore
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//controllo errori
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("> Errore colore:\n%s\n", gluErrorString(error));
		success = false;
	}

	//init audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("> SDL_mixer non inizializzato. Errore: %s\n", Mix_GetError());
		success = false;
	}
	else printf("SDL_mixer inizializzato.\n");

	//init ttf
	if (TTF_Init() == -1)
	{
		printf("> SDL_ttf non inizializzato. Errore: %s\n", TTF_GetError());
		success = false;
	} printf("SDL_ttf inizializzato.\n");
	
	return success;
}

bool initSDL()
{
	return !(SDL_Init(SDL_INIT_VIDEO) < 0);
}

bool initLauncher()
{
	//Initialization flag
	bool success = true;

	//Create window
	lWindow = SDL_CreateWindow("launcher", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 300, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS );
	if (lWindow == NULL)
	{
		printf("> launcher non creato.\nSDL_CreateWindow() Errore: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		printf("Launcher creato.\n");
		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("> Immagine launcher non caricata.\nIMG_Init() Errore: %s\n", IMG_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			printf("Immagine launcher caricata.\n");
			lScreenSurface = SDL_GetWindowSurface(lWindow);
		}
	}

	lJPGSurface = loadSurface("launcher.jpg");
	if (lJPGSurface == NULL)
	{
		printf("Impossibile trovare l'immagine del launcher.\n");
	}
	//Apply the PNG image
	SDL_BlitSurface(lJPGSurface, NULL, lScreenSurface, NULL);

	//Update the surface
	SDL_UpdateWindowSurface(lWindow);

	return success;
}

void startGame()
{
	showGame();
	hideLauncher();
	fps.start();
}

void showGame()
{
	SDL_ShowWindow(gWindow);
	gShown = true;
}

void hideLauncher()
{
	SDL_HideWindow(lWindow);
}

void hideGame()
{
	SDL_HideWindow(gWindow);
	gShown = false;
}

void freeLauncher()
{
	if (lWindow != NULL)
	{
		SDL_DestroyWindow(lWindow);
		printf("launcher distrutto.\n");
	}
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* resizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("> Impossiblie caricare l'immagine:%s!\n SDL_image Errore: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		resizedSurface = SDL_ConvertSurface(loadedSurface, lScreenSurface->format, NULL);
		if (resizedSurface == NULL)
		{
			printf("> Impossiblie ridimensionare l'immagine:%s!\n SDL_ConvertSurface Errore: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return resizedSurface;
}
bool initGame()
{
	bool success = true;
	//init variabili
	gWindow = NULL;
	gContext = NULL;

	if (gConfig.init())
	{
		gConfig.download();
		gScreenMode = gConfig.getScreenMode();
		gWidth = gConfig.getWidth();
		gHeight = gConfig.getHeight();
	}
	else
	{
		gScreenMode = 0;
		gWidth = SCREEN_WIDTH;
		gHeight = SCREEN_HEIGHT;
		printf("> Config non riuscita.\n");
	}

	gMouseFocus = false;
	gKeyboardFocus = false;
	gShown = false;
	gWindowID = -1;

	/*gScreenMode = 0;
	gWidth = SCREEN_WIDTH;
	gHeight = SCREEN_HEIGHT;*/

	//Uso OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	
	gWindow = SDL_CreateWindow("SPACE hATEr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gWidth, gHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | gScreenMode);
	if (gWindow != NULL)
	{
		gMouseFocus = true;
		gKeyboardFocus = true;
		

		//Create renderer for window
		gContext = SDL_GL_CreateContext(gWindow);
		if (gContext == NULL)
		{
			printf("> Errore SDL_GL_CreateContext():\n%s\n", SDL_GetError());
			SDL_DestroyWindow(gWindow);
			gWindow = NULL;
		}
		else
		{
			printf("Context creato.\n");

			//Grab window identifier
			gWindowID = SDL_GetWindowID(gWindow);
			printf("Finestra creata GAME.\n");
			//Flag as opened
			gShown = false;
		}
	}
	else
	{
		printf("> Errore SDL_CreateWindow():\n%s\n", SDL_GetError());
	}
	//printf("_____________________________ \n");
	success =  (gWindow != NULL && gContext != NULL);

	//Inizializzazione OpenGL
	if (!initGL())
	{
		printf("> OpenGL non inizializzato.\n");
		success = false;
	}
	else printf("OpenGL Inizializzato.\n");
	
	return success;
}

void update()
{
}

void provaMappa()
{
	//map.render();
}
//#########################################################
bool handleEvent(SDL_Event& e)
{
	bool again = true;
	again = gMenuStart.input(e) && gGameMap.input(e);
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == gWindowID)
	{
		//Caption update flag
		bool updateCaption = false;

		switch (e.window.event)
		{
			//Window appeared
		case SDL_WINDOWEVENT_SHOWN:
			gShown = true;
			break;

			//Window disappeared
		case SDL_WINDOWEVENT_HIDDEN:
			gShown = false;
			break;

			//Get new dimensions and repaint
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			gWidth = e.window.data1;
			gHeight = e.window.data2;
			resize(gWidth, gHeight);
			//SDL_RenderPresent(mRenderer);
			break;

			//Repaint on expose
		case SDL_WINDOWEVENT_EXPOSED:
			//SDL_RenderPresent(mRenderer);
			break;

			//Mouse enter
		case SDL_WINDOWEVENT_ENTER:
			gMouseFocus = true;
			updateCaption = true;
			break;

			//Mouse exit
		case SDL_WINDOWEVENT_LEAVE:
			gMouseFocus = false;
			updateCaption = true;
			break;

			//Keyboard focus gained
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			gKeyboardFocus = true;
			updateCaption = true;
			break;

			//Keyboard focus lost
		case SDL_WINDOWEVENT_FOCUS_LOST:
			gKeyboardFocus = false;
			updateCaption = true;
			break;

			//Hide on close
		case SDL_WINDOWEVENT_CLOSE:
			again = false;
			//hideGame();
			break;
		}

		//Update window caption with new data
		if (updateCaption)
		{
			std::stringstream caption;
			caption << "SPACE hATEr - ID: " << gWindowID << " MouseFocus:" << ((gMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((gKeyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(gWindow, caption.str().c_str());
		}
	}
	return again;
}

bool engineMenu()
{
	switch (ElementShown)
	{
		case 0:
			gMenuStart.show();
			ElementShown = gMenuStart.menu();
			if (ElementShown != 0)
				gMenuStart.hide();
		break;

		case 1:
			gGameMap.show();
		break;
	}
	return true;
}

bool enginePhysics()
{
	gGameMap.fisica();
	return true;
}

void engineGraphics()//dovrei fare uno switch e tenere una variabile int globale come scelta prima di renderizzare faccio fare il calcolo
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	gMenuStart.grafica();
	gGameMap.grafica();
	fps.render();
	
	SDL_GL_SwapWindow(gWindow);
}
//#########################################################

void old()
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	GLfloat vertici[] =
	{
		-0.5, -0.5, 0.0,
		0.5, -0.5, 0.0,
		0.5, 0.5, 0.0,
		-0.5, 0.5, 0.0
	};

	GLfloat colori[] =
	{
		0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 0.0

	};

	GLfloat normali[] =
	{
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0

	};

	GLbyte indici[] =
	{
		0, 1, 2, 3
	};

	glVertexPointer(3, GL_FLOAT, 0, vertici);//dichiarativa
	glColorPointer(3, GL_FLOAT, 0, colori);
	glNormalPointer(GL_FLOAT, 0, normali);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, indici);//disegnante

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void close()
{
	TTF_CloseFont(gFont);
	SDL_GL_DeleteContext(gContext);
	SDL_DestroyWindow(gWindow);
	printf("Finestra distrutta: GAME.\n");
	freeLauncher();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;
	//printf("LoadMedia________\n");

	//spinGear = 0.0;

	int d = 0;
	printf("Delay launcher (%d).\n", d);
	SDL_Delay(d);

	SDL_Color marrone = { 0x50, 0x4C, 0x4C };
	SDL_Color verde = {0x00, 0xFF, 0x00};
	SDL_Color verdeScuro = {0x00, 0xAA, 0x00};

	gFont = TTF_OpenFont("arial.ttf", 70);
	if (gFont == NULL)
	{
		printf("> Font 'arial' non caricato. Errore:\n%s\n", TTF_GetError());
		success = false;
	}
	else printf("Font 'arial' caricato.\n");

	gMenuStart.init();
	gGameMap.init();
	ElementShown = 0;

	fps.init(verde, gFont, 0, 1060, 50, 20);
	
	//----------------------------------------mappa
	//map.downLoadTexture(1920.0+1060.0, 1080.0+640.0);


	
	//printf("_________________\n");
	return success;
}
bool isQuit()
{
	return (gShown);

}

void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

