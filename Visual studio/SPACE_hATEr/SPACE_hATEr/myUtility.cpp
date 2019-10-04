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
mySlightLESS* gShader;
mySdraw* gShader2;
mySadvanceLight* gShader3;
myPipeline p1;
GLuint VBO, vbo2;
GLuint IBO, ibo2;

myFps fps;
myTexture old3;
myMesh* gMesh;
static float FieldDepth = 10.0f;
float gScale = 0.0;

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
bool initGLEW()
{
	bool success = true;
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "> Errore: '%s'.\n", glewGetErrorString(res));
		success = false;
	}
	return success;
}

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
	//glOrtho(0, 1920, 0, 1080, 1, -1);

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
	//glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	//controllo errori
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("> Errore colore:\n%s\n", gluErrorString(error));
		success = false;
	}
	
	printf("GL version: %s.\n", glGetString(GL_VERSION));

	/*glFrontFace(GL_CW);/ disegna solo facce orarie
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);*/

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	


	return success;
}

bool initSDL()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("> SDL_INIT_VIDEO non inizializzato. Errore: %s\n", Mix_GetError());
		success = false;
	}

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
		printf("Launcher creato.\n");
	
	lScreenSurface = SDL_GetWindowSurface(lWindow);
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
	p1.setPerspectiveProj(60.0f, gWidth, gHeight, 1.0f, 100.0f);
	p1.setCamera(Vector3f(0.0f, 0.0f, -1.738f), Vector3f(0.0f, 0.0f, 1.0f), Vector3f(0.0f, 1.0f, 0.0f));
	p1.worldPos(0.0f, 0.0f, 0.0f);
	
	//gShader2->enable();
	//gShader2->enable();
	gShader3->setTextureUnit(0);
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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
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
	
	if (!initGLEW())
	{
		printf("> GLEW non inizializzato.\n");
		success = false;
	}
	else printf("GLEW Inizializzato.\n");

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//old();

	gShader->enable();
	gShader->setWVP(p1.getWVPTrans());
	gMenuStart.grafica();
	gGameMap.grafica();
	fps.render();

	/*gShader2->enable();
	gShader2->setWVP(p1.getWVPTrans());*/
	//old2();

	/*
	glEnable(GL_DEPTH_TEST);
	drawMesh();
	glDisable(GL_DEPTH_TEST);*/

	SDL_GL_SwapWindow(gWindow);
}
//#########################################################

void old()
{
	if (old3.loadTextureFromFile(GL_TEXTURE_2D, "gear.png"))
		printf("old3 caricata.\n");
	Vertex Vertices[] =
	{
		Vertex(gui(Vector3f(   0.0f,    0.0f, 0.0f)), Vector2f(0.0f, 1.0f)),
		Vertex(gui(Vector3f(   0.0f, 1080.0f, 0.0f)), Vector2f(0.0f, 0.0f)),
		Vertex(gui(Vector3f(1920.0f, 1080.0f, 0.0f)), Vector2f(1.0f, 0.0f)),
		Vertex(gui(Vector3f(1920.0f,    0.0f, 0.0f)), Vector2f(1.0f, 1.0f))
	};
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	unsigned int Indices[] =
	{
		0,1,2,3
	};

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);


}

void old2()
{

	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float)* 3));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);


}

void initOld2()
{
	old();
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

	initShader();

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
	//initOld2();
	//----------------------------------------mappa
	//map.downLoadTexture(1920.0+1060.0, 1080.0+640.0);


	
	//printf("_________________\n");

	gMesh = new myMesh();
	if (!gMesh->loadMesh("mesh/phoenix_ugv.md2"))
	{
		printf("> Load mesh fallito.\n");
		success = false;
	}
	else printf("Load mesh.\n");

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

void initShader()
{
	printf("________________SHADER\n");
	gShader = new mySlightLESS();
	if (!gShader->init())
	{
		printf("> Errore init lightLESS.\n");
	}
	else printf("Shader lightLESS caricato.\n");


	gShader2 = new mySdraw();
	if (!gShader2->init())
	{
		printf("> Errore init draw.\n");
	}
	else printf("Shader draw caricato.\n");


	gShader3 = new mySadvanceLight();
	if (!gShader3->init())
	{
		printf("> Errore init advLight.\n");
	}
	else printf("Shader advLight caricato.\n");
	printf("_____________________\n");
}

void drawMesh()
{

	Vector3f Pos(3.0f, 7.0f, -10.0f);
	Vector3f Target(0.0f, -0.2f, 1.0f);
	Vector3f Up(0.0, 1.0f, 0.0f);

	Up.normalize();
	Target.normalize();

	gShader3->enable();
	

	gScale += 0.01f;

	directionalLight m_directionalLight;
	m_directionalLight.color = Vector3f(1.0f, 1.0f, 1.0f);
	m_directionalLight.ambientIntensity = 1.0f;
	m_directionalLight.diffuseIntensity = 0.01f;
	m_directionalLight.direction = Vector3f(1.0f, -1.0, 0.0);

	pointLight pl[2];
	pl[0].diffuseIntensity = 0.25f;
	pl[0].color = Vector3f(1.0f, 0.5f, 0.0f);
	pl[0].position = Vector3f(3.0f, 1.0f, FieldDepth * (cosf(gScale) + 1.0f) / 2.0f);
	pl[0].attenuation.linear = 0.1f;

	pl[1].diffuseIntensity = 0.25f;
	pl[1].color = Vector3f(0.0f, 0.5f, 1.0f);
	pl[1].position = Vector3f(7.0f, 1.0f, FieldDepth * (sinf(gScale) + 1.0f) / 2.0f);
	pl[1].attenuation.linear = 0.1f;
	gShader3->setPointLights(2, pl);

	spotLight sl[2];
	sl[0].diffuseIntensity = 0.9f;
	sl[0].color = Vector3f(0.0f, 1.0f, 1.0f);
	sl[0].position = Pos;
	sl[0].direction = Target;
	sl[0].attenuation.linear = 0.1f;
	sl[0].cutoff = 10.0f;

	sl[1].diffuseIntensity = 0.75f;
	sl[1].color = Vector3f(0.0f, 0.5f, 1.0f);
	sl[1].position = Vector3f(7.0f, 1.0f, FieldDepth * (sinf(gScale) + 1.0f) / 2.0f);
	sl[1].attenuation.linear = 0.1f;
	gShader3->setSpotLights(1, sl);

	myPipeline p;
	p.scale(0.1f, 0.1f, 0.1f);
	p.rotate(0.0f, gScale, 0.0f);
	p.worldPos(0.0f, 0.0f, 10.0f);
	p.setCamera(Pos, Target, Up);
	p.setPerspectiveProj(60.0f, gWidth, gHeight, 1.0f, 200.0f);

	gShader3->setWVP(p.getWVPTrans());
	gShader3->setWorldMatrix(p.getWorldTrans());
	gShader3->setDirectionalLight(m_directionalLight);
	gShader3->setEyeWorldPos(Pos);
	gShader3->setMatSpecularIntensity(0.0f);
	gShader3->setMatSpecularPower(0);

	gMesh->Render();
}