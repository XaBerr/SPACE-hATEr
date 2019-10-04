#include "myShip.h"

myShip::myShip()
{
	spinShip = 90.0;
}

myShip::~myShip()
{
	spinShip = 90.0;
}

bool myShip::init()
{
	return mShipTexture.loadTextureFromFile(GL_TEXTURE_2D, "map/Spaceship.png");
	//return true;
}

void myShip::render()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated(960,540,0);
	glRotatef(spinShip, 0.0, 0.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mShipTexture.getID());

	
	glBegin(GL_QUADS);
		glTexCoord3f(1.0, 1.0, 0.0);
		glVertex3i( -70, -80, 0);
		glTexCoord3f(0.0, 1.0, 0.0);
		glVertex3i( -70, +80, 0);
		glTexCoord3f(0.0, 0.0, 0.0);
		glVertex3i( +70, +80, 0);
		glTexCoord3f(1.0, 0.0, 0.0);
		glVertex3i( +70, -80, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glLoadIdentity();
	

}

void myShip::move(float alpha)
{
	spinShip = (alpha * 360) / (2 * M_PI);//trasformo in gradi
	//printf("spinShip (%f)\n",spinShip);
}