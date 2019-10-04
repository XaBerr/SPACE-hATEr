#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>

#ifndef _myTexture
#define _myTexture 1



class myTexture
{
	public:
		myTexture();
		myTexture(GLenum textureTarget, const std::string& path);
		~myTexture();
		myTexture& operator = ( myTexture& x);

		bool loadTextureFromFile(GLenum textureTarget, std::string path);
		bool loadTTF(std::string textureText, SDL_Color textColor, TTF_Font *mFont);
		bool loadMesh();

		void free();
		void render(GLfloat x, GLfloat y);
		void bind(GLenum textureUnit);
		

		void setID(int id);
		void setColors(int colors);
		void setWidth(int w);
		void setHeight(int h);

		GLuint getID();
		GLint getColors();
		int getWidth();
		int getHeight();

		
	private:
		GLuint mID;
		GLenum mTextureFormat;
		GLint mColors;
		GLenum mTextureTarget;
		int mWidth;
		int mHeight;
		std::string mPath;

};

#endif // !_myTexture