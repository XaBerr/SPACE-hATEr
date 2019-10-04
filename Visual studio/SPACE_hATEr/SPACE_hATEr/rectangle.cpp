#include "rectangle.h"

rectangle::rectangle()
{
	mIBO = NULL;
	mVBO = NULL;
}
rectangle::~rectangle()
{

}
void rectangle::init(int x, int y, int w, int h)
{
	Vertex Vertices[] =
	{
		Vertex(Vector3f(x, y, 0.0), Vector2f(0.0f, 1.0f)),
		Vertex(Vector3f(x, y + h, 0.0), Vector2f(0.0f, 0.0f)),
		Vertex(Vector3f(x + w, y + h, 0.0), Vector2f(1.0f, 0.0f)),
		Vertex(Vector3f(x + w, y, 0.0), Vector2f(1.0f, 1.0f))
	};


	unsigned int Indices[] =
	{
		0, 1, 2, 3
	};

	
	GLuint tVBO;
	GLuint tIBO;

	glGenBuffers(1, &tVBO);
	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &tIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	mVBO = tVBO;
	mIBO = tIBO;
	printf("Init rectangle.\n");

}
void rectangle::initGui(int x, int y, int w, int h)
{
	Vertex Vertices[] =
	{
		Vertex(gui(Vector3f(x, y, 0.0)), Vector2f(0.0f, 1.0f)),
		Vertex(gui(Vector3f(x, y + h, 0.0)), Vector2f(0.0f, 0.0f)),
		Vertex(gui(Vector3f(x + w, y + h, 0.0)), Vector2f(1.0f, 0.0f)),
		Vertex(gui(Vector3f(x + w, y, 0.0)), Vector2f(1.0f, 1.0f))
	};


	unsigned int Indices[] =
	{
		0, 1, 2, 3
	};


	GLuint tVBO;
	GLuint tIBO;

	glGenBuffers(1, &tVBO);
	glBindBuffer(GL_ARRAY_BUFFER, tVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &tIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	mVBO = tVBO;
	mIBO = tIBO;
	printf("Init rectangle.\n");

}
void rectangle::init(GLuint tVBO, GLuint tIBO)
{
	mVBO = tVBO;
	mIBO = tIBO;

}

void rectangle::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(sizeof (float)* 3));

	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

