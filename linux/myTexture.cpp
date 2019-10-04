#include"myTexture.h"

myTexture& myTexture::operator = ( myTexture& x)
{
	this->setColors(x.getColors());
	this->setHeight(x.getHeight());
	this->setID(x.getID());
	this->setWidth(x.getWidth());
	printf("(colors: %d-%d height: %d-%d id: %d-%d width: %d-%d )\n", x.getColors(),this->getColors(), x.getHeight(),this->getHeight(), x.getID(),this->getID(), x.getWidth(), this->getWidth());
	return *this;
}
myTexture::myTexture()
{
	mID = -1;
	mWidth = 0;
	mHeight = 0;
	mColors = 0;
}

myTexture::~myTexture()
{
	this->free();
}

void myTexture::free()
{
	//Delete texture
	glDeleteTextures(1, &mID);
	mID = -1;
	mWidth = 0;
	mHeight = 0;
	mColors = 0;
}

void myTexture::setID(int id)
{
	mID = id;
}

void myTexture::setColors(int colors)
{
	mColors = colors;
}


void myTexture::setWidth(int w)
{
	mWidth = w;
}

void myTexture::setHeight(int h)
{
	mHeight = h;
}
//*****get
GLuint myTexture::getID()
{
	return mID;
}

GLint myTexture::getColors()
{
	return mColors;
}


int myTexture::getWidth()
{
	return mWidth;
}

int myTexture::getHeight()
{
	return mHeight;
}

bool myTexture::loadTextureFromFile(std::string path)
{
	bool success = true;
	if (mID != -1)
		free();
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf("> Impossibile caricare l'immagine %.! Errore: %s\n", path.c_str(), IMG_GetError());
		success = false;
	}
	else
	{
		mColors = loadedSurface->format->BytesPerPixel;
		if (mColors == 4)
		{
			if (loadedSurface->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA_EXT;
		}
		else if (mColors == 3)
		{
			if (loadedSurface->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR_EXT;
		}
		else
		{
			printf("> Errore caricamento texture.\n");
			success = false;
		}
		glGenTextures(1, &mID);//genera un id

		glBindTexture(GL_TEXTURE_2D, mID);//aggiunge l'id all'area di memoria delle txtr2d
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//setta parametri di streach
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, mColors, loadedSurface->w, loadedSurface->h, 0, texture_format, GL_UNSIGNED_BYTE, loadedSurface->pixels);//carica la txtr in memoria
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		printf("Texture(%d), W(%d), H(%d), Mode(%0x).\n", mID, loadedSurface->w, loadedSurface->h, texture_format);

	}
	return success;
}

bool myTexture::loadTTF(std::string textureText, SDL_Color textColor, TTF_Font *mFont)
{
	bool success = true;
	if (mID != -1)
		free();
	//Render text surface
		SDL_Surface* loadedSurface = TTF_RenderText_Blended(mFont, textureText.c_str(), textColor);

	if (loadedSurface == NULL)
	{
		printf("> Impossibile caricare il font %.! Errore: %s\n", textureText.c_str(), IMG_GetError());//da lavorarci
		success = false;
	}
	else
	{
		mColors = GL_RGBA;
		texture_format = GL_RGBA;

		glGenTextures(1, &mID);//genera un id

		glBindTexture(GL_TEXTURE_2D, mID);//aggiunge l'id all'area di memoria delle txtr2d
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//setta parametri di streach
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadedSurface->w, loadedSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, loadedSurface->pixels);//carica la txtr in memoria
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
		//printf("Texture(%d), W(%d), H(%d), Mode(%0x).\n", mID, loadedSurface->w, loadedSurface->h, texture_format);

	}
	return success;

}