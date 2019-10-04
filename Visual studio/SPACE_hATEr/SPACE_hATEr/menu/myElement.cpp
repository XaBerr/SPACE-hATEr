#include "myElement.h"

myElement::myElement()
{
	mShown = false;
}

myElement::~myElement()
{
	mShown = false;
}

bool myElement::input(SDL_Event& e)
{
	return false;
}

void myElement::fisica()
{}

void myElement::grafica()
{}

void myElement::show()
{
	mShown = true;
}

void myElement::hide()
{
	mShown = false;
}

bool myElement::isShown()
{
	return mShown;
}