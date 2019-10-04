#include"myWindow.h"


myWindow::myWindow()
{
	//Initialize non-existant window
	mWindow = NULL;
	mContext = NULL;

	mMouseFocus = false;
	mKeyboardFocus = false;
	mFullScreen = false;
	mShown = false;
	mWindowID = -1;

	mWidth = 0;
	mHeight = 0;
}

bool myWindow::init()
{
	//printf("\nInitWindowSDL________________ \n");
	//Create window
	mWindow = SDL_CreateWindow("SPACE hATEr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
	if (mWindow != NULL)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

		//Create renderer for window
		mContext = SDL_GL_CreateContext(mWindow);
		if (mContext == NULL)
		{
			printf("Errore SDL_GL_CreateContext():\n%s\n", SDL_GetError());
			SDL_DestroyWindow(mWindow);
			mWindow = NULL;
		}
		else
		{
			printf("Context creato.\n");

			//Grab window identifier
			mWindowID = SDL_GetWindowID(mWindow);
			printf("Finestra creata (%d).\n", mWindowID);
			//Flag as opened
			mShown = false;
		}
	}
	else
	{
		printf("Errore SDL_CreateWindow():\n%s\n", SDL_GetError());
	}
	//printf("_____________________________ \n");
	return mWindow != NULL && mContext != NULL;
}
bool myWindow::init(int flag)
{
	//printf("\nInitWindowSDL________________ \n");
	//Create window
	mWindow = SDL_CreateWindow("SPACE hATEr", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flag);
	if (mWindow != NULL)
	{
		mMouseFocus = true;
		mKeyboardFocus = true;
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;

		//Create renderer for window
		mContext = SDL_GL_CreateContext(mWindow);
		if (mContext == NULL)
		{
			printf("Errore SDL_GL_CreateContext():\n%s\n", SDL_GetError());
			SDL_DestroyWindow(mWindow);
			mWindow = NULL;
		}
		else
		{
			printf("Context creato.\n");

			//Grab window identifier
			mWindowID = SDL_GetWindowID(mWindow);
			printf("Finestra creata (%d).\n", mWindowID);
			//Flag as opened
			mShown = false;
		}
	}
	else
	{
		printf("Errore SDL_CreateWindow():\n%s\n", SDL_GetError());
	}
	//printf("_____________________________ \n");
	return mWindow != NULL && mContext != NULL;
}

void myWindow::handleEvent(SDL_Event& e)//#########################################################da sistemare
{
	//If an event was detected for this window
	if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID)
	{
		//Caption update flag
		bool updateCaption = false;

		switch (e.window.event)
		{
			//Window appeared
		case SDL_WINDOWEVENT_SHOWN:
			mShown = true;
			break;

			//Window disappeared
		case SDL_WINDOWEVENT_HIDDEN:
			mShown = false;
			break;

			//Get new dimensions and repaint
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			this->myWindow::resize(mWidth, mHeight);
			//SDL_RenderPresent(mRenderer);
			break;

			//Repaint on expose
		case SDL_WINDOWEVENT_EXPOSED:
			//SDL_RenderPresent(mRenderer);
			break;

			//Mouse enter
		case SDL_WINDOWEVENT_ENTER:
			mMouseFocus = true;
			updateCaption = true;
			break;

			//Mouse exit
		case SDL_WINDOWEVENT_LEAVE:
			mMouseFocus = false;
			updateCaption = true;
			break;

			//Keyboard focus gained
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			mKeyboardFocus = true;
			updateCaption = true;
			break;

			//Keyboard focus lost
		case SDL_WINDOWEVENT_FOCUS_LOST:
			mKeyboardFocus = false;
			updateCaption = true;
			break;

			//Hide on close
		case SDL_WINDOWEVENT_CLOSE:
			this->hide();
			break;
		}

		//Update window caption with new data
		if (updateCaption)
		{
			std::stringstream caption;
			caption << "SPACE hATEr - ID: " << mWindowID << " MouseFocus:" << ((mMouseFocus) ? "On" : "Off") << " KeyboardFocus:" << ((mKeyboardFocus) ? "On" : "Off");
			SDL_SetWindowTitle(mWindow, caption.str().c_str());
		}
	}
}
void myWindow::resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void myWindow::focus()
{
	//Restore window if needed
	if (!mShown)
	{
		SDL_ShowWindow(mWindow);
	}

	//Move window forward
	SDL_RaiseWindow(mWindow);
}

void myWindow::render()
{
	//Update screen
	SDL_GL_SwapWindow(mWindow);

}

void myWindow::free()
{
	if (mWindow != NULL)
	{
		SDL_GL_DeleteContext(mContext);
		SDL_DestroyWindow(mWindow);
		printf("Finestra distrutta: %d.\n", mWindowID);
	}

	mMouseFocus = false;
	mKeyboardFocus = false;
	mWidth = 0;
	mHeight = 0;
}

int myWindow::getWidth()
{
	return mWidth;
}

int myWindow::getHeight()
{
	return mHeight;
}

bool myWindow::hasMouseFocus()
{
	return mMouseFocus;
}

bool myWindow::hasKeyboardFocus()
{
	return mKeyboardFocus;
}

bool myWindow::isShown()
{
	return mShown;
}

void myWindow::show()
{
	SDL_ShowWindow(this->myWindow::mWindow);
	this->mShown = true;
	printf("Show finestra (%d).\n", myWindow::mWindowID);
}

void myWindow::hide()
{
	SDL_HideWindow(this->myWindow::mWindow);
	this->mShown = false;
	printf("Hide finestra (%d).\n", myWindow::mWindowID);
}