#include "menuStart.h"
menuStart::menuStart() :myElement()
{
	//myElement::myElement();
	mFont = NULL;
}
menuStart::~menuStart()
{
	//TTF_CloseFont(mFont); lancia eccezioni
	myElement::~myElement();
}

bool menuStart::input(SDL_Event& e)
{
	if (!mShown)
		return true;
	mContinua.handleEvent(e);
	mNuova.handleEvent(e);
	mOpzioni.handleEvent(e);
	mEsci.handleEvent(e);
	if (mEsci.isClick())
		return false;
	return true;
}

int menuStart::menu()
{
	if (mContinua.isClick())
		return 1;
	if (mNuova.isClick())
		return 2;
	if (mOpzioni.isClick())
		return 3;
	return 0;
}

void menuStart::grafica()
{
	if (!mShown)
		return;
	//glColor3f(1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	spinGear += 0.8;
	if (spinGear > 360.0)
		spinGear -= 360.0;

	glTranslatef(1650, 830, 0.0);
	glRotatef(spinGear, 0.0, 0.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gear.getID());

	glBegin(GL_POLYGON);
	glTexCoord3f(0.0, 0.0, 0.0);
	glVertex3f(-50, -50, 0.0);

	glTexCoord3f(0.0, 1.0, 0.0);
	glVertex3f(-50, +50, 0.0);

	glTexCoord3f(1.0, 1.0, 0.0);
	glVertex3f(+50, +50, 0.0);

	glTexCoord3f(1.0, 0.0, 0.0);
	glVertex3f(+50, -50, 0.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glLoadIdentity();

	glTranslatef(1585, 770, 0.0);
	glRotatef(-(spinGear + 30), 0.0, 0.0, 1.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gear.getID());

	glBegin(GL_POLYGON);
	glTexCoord3f(0.0, 0.0, 0.0);
	glVertex3f(-50, -50, 0.0);

	glTexCoord3f(0.0, 1.0, 0.0);
	glVertex3f(-50, +50, 0.0);

	glTexCoord3f(1.0, 1.0, 0.0);
	glVertex3f(+50, +50, 0.0);

	glTexCoord3f(1.0, 0.0, 0.0);
	glVertex3f(+50, -50, 0.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glLoadIdentity();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1080, 0);
	glVertex3f(1920, 1080, 0);
	glVertex3f(1920, 1, 0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);

	mContinua.render();
	mNuova.render();
	mOpzioni.render();
	mEsci.render();
}

bool menuStart::init()
{
	bool success = true;
	spinGear = 0.0;
	SDL_Color grigio = { 0x50, 0x4C, 0x4C };
	SDL_Color verde = { 0x00, 0xFF, 0x00 };
	SDL_Color verdeScuro = { 0x00, 0xAA, 0x00 };

	mFont = TTF_OpenFont("arial.ttf", 70);
	if (mFont == NULL)
	{
		printf("> Font 'arial' non caricato. Errore:\n%s\n", TTF_GetError());
		success = false;
	}
	else printf("Font 'arial' caricato.\n");

	mContinuaTexture[0].loadTTF("Continua", grigio, mFont);
	mContinuaTexture[1].loadTTF("Continua", verde, mFont);
	mContinuaTexture[2].loadTTF("Continua", verdeScuro, mFont);
	mContinua.init(200, 100, mContinuaTexture[0].getWidth(), mContinuaTexture[0].getHeight(), mContinuaTexture[0].getID(), mContinuaTexture[1].getID(), mContinuaTexture[2].getID(), MY_TYPE_TXT);
	mContinua.show();
	//mContinua.lock();

	mNuovaTexture[0].loadTTF("Nuova", grigio, mFont);
	mNuovaTexture[1].loadTTF("Nuova", verde, mFont);
	mNuovaTexture[2].loadTTF("Nuova", verdeScuro, mFont);
	mNuova.init(600, 100, mNuovaTexture[0].getWidth(), mNuovaTexture[0].getHeight(), mNuovaTexture[0].getID(), mNuovaTexture[1].getID(), mNuovaTexture[2].getID(), MY_TYPE_TXT);
	mNuova.show();
	mNuova.lock();

	mOpzioniTexture[0].loadTTF("Opzioni", grigio, mFont);
	mOpzioniTexture[1].loadTTF("Opzioni", verde, mFont);
	mOpzioniTexture[2].loadTTF("Opzioni", verdeScuro, mFont);
	mOpzioni.init(1000, 100, mOpzioniTexture[0].getWidth(), mOpzioniTexture[0].getHeight(), mOpzioniTexture[0].getID(), mOpzioniTexture[1].getID(), mOpzioniTexture[2].getID(), MY_TYPE_TXT);
	mOpzioni.show();
	mOpzioni.lock();

	mEsciTexture[0].loadTTF("Esci", grigio, mFont);
	mEsciTexture[1].loadTTF("Esci", verde, mFont);
	mEsciTexture[2].loadTTF("Esci", verdeScuro, mFont);
	mEsci.init(1400, 100, mEsciTexture[0].getWidth(), mEsciTexture[0].getHeight(), mEsciTexture[0].getID(), mEsciTexture[1].getID(), mEsciTexture[2].getID(), MY_TYPE_TXT);
	mEsci.show();

	if (gear.loadTextureFromFile(GL_TEXTURE_2D, "gear.png"))
		printf("Gear caricata.\n");

	return success;
}

void menuStart::show()
{
	myElement::show();
}

void menuStart::hide()
{
	myElement::hide();
}