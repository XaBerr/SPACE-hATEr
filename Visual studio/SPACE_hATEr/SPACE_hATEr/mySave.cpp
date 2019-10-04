#include "mySave.h"

mySave::mySave()
{
	mLoad = false;
	mNomeFile = "";
}
mySave::~mySave()
{
	SDL_FreeRW(mFile);
}
void mySave::init(std::string file)
{
	mNomeFile = file;
}
void mySave::save()
{
	
}
void mySave::addSave()
{
}
void mySave::load()
{
	mFile = SDL_RWFromFile(mNomeFile.c_str(), "r+b");
	if (mFile == NULL)
	{
		printf("Warning: Unable to open file! SDL Error: %s\n", SDL_GetError());

		//Create file for writing
		mFile = SDL_RWFromFile("nums.bin", "w+b");//                          <###########################(write+bin)
		if (mFile != NULL)
		{
			printf("New file created!\n");
		}
	}


	SDL_RWclose(mFile);
}
void mySavedeleteSave()
{
}
void mySave::newSave()
{
}
/*int * mySave::returnSave()
{
	int salvataggi[30];
	char temp[30];
	bool flag = true;
	int i = 0;
	sprintf(temp, "saveData%d.save", i);
	while (flag)
	{
		if (SDL_RWFromFile("nums.bin", "w+b") == NULL)
			flag = false;
		else
		{
			salvataggi[i] = i;
			sprintf(temp, "saveData%d.save", ++i);
		}
	}
	return salvataggi;
}*/