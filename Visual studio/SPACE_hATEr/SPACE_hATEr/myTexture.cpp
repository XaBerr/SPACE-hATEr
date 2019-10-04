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

myTexture::myTexture(GLenum textureTarget, const std::string& path)
{
	mTextureTarget = textureTarget;
	mPath = path;
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

bool myTexture::loadTextureFromFile(GLenum textureTarget, std::string path)
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
				mTextureFormat = GL_RGBA;
			else
				mTextureFormat = GL_BGRA_EXT;
		}
		else if (mColors == 3)
		{
			if (loadedSurface->format->Rmask == 0x000000ff)
				mTextureFormat = GL_RGB;
			else
				mTextureFormat = GL_BGR_EXT;
		}
		else
		{
			printf("> Errore caricamento texture.\n");
			success = false;
		}

		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
		mTextureTarget = textureTarget;

		glGenTextures(1, &mID);//genera un id
		glBindTexture(mTextureTarget, mID);//aggiunge l'id all'area di memoria delle txtr2d
		glTexParameteri(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//setta parametri di streach
		glTexParameteri(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(mTextureTarget, 0, mColors, mWidth, mHeight, 0, mTextureFormat, GL_UNSIGNED_BYTE, loadedSurface->pixels);//carica la txtr in memoria
		
		SDL_FreeSurface(loadedSurface);
		printf("Texture(%d), W(%d), H(%d), Format(%0x), Target(%0x).\n", mID, mWidth, mHeight, mTextureFormat, mTextureTarget);

	}
	return success;
}

bool myTexture::loadMesh()
{
	bool success = true;
	if (mID != -1)
		free();
	SDL_Surface* loadedSurface = IMG_Load(mPath.c_str());

	if (loadedSurface == NULL)
	{
		printf("> Impossibile caricare l'immagine %.! Errore: %s\n", mPath.c_str(), IMG_GetError());
		success = false;
	}
	else
	{
		mColors = loadedSurface->format->BytesPerPixel;
		if (mColors == 4)
		{
			if (loadedSurface->format->Rmask == 0x000000ff)
				mTextureFormat = GL_RGBA;
			else
				mTextureFormat = GL_BGRA_EXT;
		}
		else if (mColors == 3)
		{
			if (loadedSurface->format->Rmask == 0x000000ff)
				mTextureFormat = GL_RGB;
			else
				mTextureFormat = GL_BGR_EXT;
		}
		else
		{
			printf("> Errore caricamento texture.\n");
			success = false;
		}

		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
		
		glGenTextures(1, &mID);//genera un id
		glBindTexture(mTextureTarget, mID);//aggiunge l'id all'area di memoria delle txtr2d
		glTexParameteri(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//setta parametri di streach
		glTexParameteri(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(mTextureTarget, 0, mColors, mWidth, mHeight, 0, mTextureFormat, GL_UNSIGNED_BYTE, loadedSurface->pixels);//carica la txtr in memoria

		SDL_FreeSurface(loadedSurface);
		printf("Texture(%d), W(%d), H(%d), Format(%0x), Target(%0x).\n", mID, mWidth, mHeight, mTextureFormat, mTextureTarget);

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
		mTextureFormat = GL_RGBA;
		mTextureTarget = GL_TEXTURE_2D;
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;
		
		glGenTextures(1, &mID);//genera un id
		glBindTexture(mTextureTarget, mID);//aggiunge l'id all'area di memoria delle txtr2d
		glTexParameterf(mTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//setta parametri di streach
		glTexParameterf(mTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(mTextureTarget, 0, mColors, mWidth, mHeight, 0, mTextureFormat, GL_UNSIGNED_BYTE, loadedSurface->pixels);//carica la txtr in memoria
		
		SDL_FreeSurface(loadedSurface);
		//printf("TextureTTF(%d), W(%d), H(%d), Format(%0x), Target(%0x).\n", mID, mWidth, mHeight, mTextureFormat, mTextureTarget);

	}
	return success;

}

void myTexture::bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(mTextureTarget, mID);
}