#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "GL/freeglut.h"
#include <string>

#ifndef _myTexture
#define _myTexture 1



class myTexture
{
	public:
		myTexture();
		~myTexture();
		myTexture& operator = ( myTexture& x);
		bool loadTextureFromFile(std::string path);
		bool loadTTF(std::string textureText, SDL_Color textColor, TTF_Font *mFont);
		void free();
		void render(GLfloat x, GLfloat y);
		void setID(int id);
		void setColors(int colors);
		void setWidth(int w);
		void setHeight(int h);
		GLuint getID();
		GLint getColors();
		int getWidth();
		int getHeight();
		bool prova1(std::string path);
		bool prova2(std::string path);
		
	private:
		GLuint mID;
		GLenum texture_format;
		GLint mColors;
		int mWidth;
		int mHeight;

};

#endif // !_myTexture