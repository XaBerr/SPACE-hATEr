#include <GL/glew.h>
#include <GL/freeglut.h>
#include "myMath.h"

#ifndef _rectangle
#define _rectangle 1

class rectangle
{
	public:
		rectangle();
		~rectangle();
		void init(GLuint tVBO, GLuint tIBO);
		void init(int x, int y, int w, int h);
		void initGui(int x, int y, int w, int h);
		void draw();

		GLuint mVBO;
		GLuint mIBO;
};

#endif // !_rectangle