#include "myMap.h"

myMap::myMap()
{
	mX = 0;
	mY = 0;
	mLoad = false;
}

myMap::~myMap()
{

}

bool myMap::isTextureLoad()
{
	return mLoad;
}

void myMap::coord4v(float x, float y, float xy[8])
{
	//ottengo le coordinate dei 4 vertici
	xy[0] = x - (1920 / 2);
	xy[1] = y - (1080 / 2);
	printf("  x1 (%f) y1 (%f)\n", xy[0], xy[1]);

	xy[2] = xy[0];
	xy[3] = y + (1080 / 2);
	printf("  x2 (%f) y2 (%f)\n", xy[2], xy[3]);

	xy[4] = x + (1920 / 2);
	xy[5] = xy[3];
	printf("  x3 (%f) y3 (%f)\n", xy[4], xy[5]);

	xy[6] = xy[4];
	xy[7] = xy[1];
	printf("  x4 (%f) y4 (%f)\n", xy[6], xy[7]);

	printf("righa-colonna:\n");
	//ottengo la riga e la colonna della mia griglia map.txt
	xy[0] = (int)(xy[0] / DIM_BLK_X);
	xy[1] = (int)(xy[1] / DIM_BLK_Y);
	printf("  x1 (%f) y1 (%f)\n", xy[0], xy[1]);

	xy[2] = (int)(xy[2] / DIM_BLK_X);
	xy[3] = (int)(xy[3] / DIM_BLK_Y);
	printf("  x2 (%f) y2 (%f)\n", xy[2], xy[3]);

	xy[4] = (int)(xy[4] / DIM_BLK_X);
	xy[5] = (int)(xy[5] / DIM_BLK_Y);
	printf("  x3 (%f) y3 (%f)\n", xy[4], xy[5]);

	xy[6] = (int)(xy[6] / DIM_BLK_X);
	xy[7] = (int)(xy[7] / DIM_BLK_Y);
	printf("  x4 (%f) y4 (%f)\n", xy[6], xy[7]);
}

bool myMap::downLoadTexture(float x, float y)
{
	mLoad = true;

	printf("______Map\n");
	//salvo la x e y
	mX = x;
	mY = y;
	printf("mX (%f) mY (%f)\n",mX,mY);

	printf("coordinate:\n");
	
	coord4v(x, y, mXY);

	//ottengo il nome delle texture 
	std::stringstream txt1;
	txt1 << "map/map" << mXY[0] << "-" << mXY[1] << ".jpg";//da ottimizzare con un ciclo
	printf("mappa 1: %s\n", txt1.str().c_str());

	std::stringstream txt2;
	txt2 << "map/map" << mXY[2] << "-" << mXY[3] << ".jpg";
	printf("mappa 2: %s\n", txt2.str().c_str());

	std::stringstream txt3;
	txt3 << "map/map" << mXY[4] << "-" << mXY[5] << ".jpg";
	printf("mappa 3: %s\n", txt3.str().c_str());

	std::stringstream txt4;
	txt4 << "map/map" << mXY[6] << "-" << mXY[7] << ".jpg";
	printf("mappa 4: %s\n", txt4.str().c_str());
	

	//carico le coordinate delle texture
	for (int i = 0; i < 4; i++)
		mMap[i].initGui(mXY[i * 2] * DIM_BLK_X, mXY[i * 2 + 1] * DIM_BLK_Y, mXY[i * 2] * DIM_BLK_X + DIM_BLK_X, mXY[i * 2 + 1] * DIM_BLK_Y + DIM_BLK_Y);

	//carico le texture
	if (!mBotLeft.loadTextureFromFile(GL_TEXTURE_2D, txt1.str()))
		if (!mBotLeft.loadTextureFromFile(GL_TEXTURE_2D, "map/default.jpg"))
				mLoad = false;

	if (!mTopLeft.loadTextureFromFile(GL_TEXTURE_2D, txt2.str()))
		if (!mTopLeft.loadTextureFromFile(GL_TEXTURE_2D, "map/default.jpg"))
			mLoad = false;

	if (!mTopRight.loadTextureFromFile(GL_TEXTURE_2D, txt3.str()))
		if (!mTopRight.loadTextureFromFile(GL_TEXTURE_2D, "map/default.jpg"))
			mLoad = false;

	if (!mBotRight.loadTextureFromFile(GL_TEXTURE_2D, txt4.str()))
		if (!mBotRight.loadTextureFromFile(GL_TEXTURE_2D, "map/default.jpg"))
			mLoad = false;

		float a = (mXY[0] * DIM_BLK_X);
		float b = (mXY[1] * DIM_BLK_Y);
		float c = ((mXY[0] * DIM_BLK_X) + DIM_BLK_X);
		float d = ((mXY[1] * DIM_BLK_Y) + DIM_BLK_Y);
	printf("a (%f) b(%f) c(%f) d(%f)\n",a,b,c,d);

	return mLoad;
}

void myMap::render()
{
	if (!mLoad)
		return;
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	
	//salvo il contest
	glPushMatrix();

	//posiziono il cursore all' "origine"
	glLoadIdentity();
	glTranslatef((DIM_BLK_X / 2) - mX, (DIM_BLK_Y / 2) - mY, 0);
	
	for (int i = 0; i < 4; i++)
	{
		if (i==0)
			glBindTexture(GL_TEXTURE_2D, mBotLeft.getID());
		if (i==1)
			glBindTexture(GL_TEXTURE_2D, mTopLeft.getID());
		if (i==2)
			glBindTexture(GL_TEXTURE_2D, mTopRight.getID());
		if (i==3)
			glBindTexture(GL_TEXTURE_2D, mBotRight.getID());
		//glColor3f(0.0, 1.0, 0.0);
		/*glBegin(GL_POLYGON);
		//bot - sx
		glTexCoord3f(0.0, 1.0, 0.0);
		glVertex3f((mXY[(i*2)] * DIM_BLK_X), (mXY[(i*2+1)] * DIM_BLK_Y), 0.0);
		//top - sx
		glTexCoord3f(0.0, 0.0, 0.0);
		glVertex3f((mXY[(i * 2)] * DIM_BLK_X), (mXY[(i*2+1)] * DIM_BLK_Y) + DIM_BLK_Y, 0.0);
		//top - dx
		glTexCoord3f(1.0, 0.0, 0.0);
		glVertex3f((mXY[(i * 2)] * DIM_BLK_X) + DIM_BLK_X, (mXY[(i*2+1)] * DIM_BLK_Y) + DIM_BLK_Y, 0.0);
		//bot - dx
		glTexCoord3f(1.0, 1.0, 0.0);
		glVertex3f((mXY[(i * 2)] * DIM_BLK_X) + DIM_BLK_X, (mXY[(i*2+1)] * DIM_BLK_Y), 0.0);
		glEnd();*/
		mMap[i].draw();
	}
	
	
	
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();

}

void myMap::move(float x, float y)
{
	bool diverso = false;

	coord4v(x, y, mNewXY);

	for (int i = 0; i < 8; i++)
		if (mXY[i] != mNewXY[i])
			diverso = true;

	if (diverso)
	{
		downLoadTexture(x,y);
		for (int i = 0; i < 8; i++)
			mXY[i] = mNewXY[i];
	}

	mX = x;
	mY = y;
	printf("mX(%f) mY(%f) x(%f) y(%f)",mX,mY,x,y);
}