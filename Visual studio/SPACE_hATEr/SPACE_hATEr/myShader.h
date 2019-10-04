#include <list>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>

#ifndef _myShader
#define _myShader 1

class myShader
{
	public:

		myShader();
		~myShader();
		virtual bool init();
		void enable();

	protected:
		bool addShader(GLenum ShaderType, const char* pShaderText);
		bool finalize();
		GLint getUniformLocation(const char* pUniformName);

	private:
		GLuint mShaderProg;
		typedef std::list<GLuint> ShaderObjList;
		ShaderObjList mShaderObjList;
};

#endif // !_myShader