#include "myConfig.h"
/*
std::fstream  &operator >>(std::fstream &fin, std::string &a)
{
	fin.read((char*)&a, sizeof(std::string));
	return fin;
}

//------------------------------------------------------------------------------
std::fstream  &operator <<(std::fstream &fout, std::string &a)
{
	fout.write((char*)&a, sizeof(std::string));
	return fout;
}*/


myConfig::myConfig()
{
	mVar[my_Resolution]   = 3;
	mVar[my_Vshync]       = 0;
	mVar[my_ScreenMode]   = 0;//(1)full - (0)windowed - (4097)deskWindowed
	mVar[my_VolumeMusic]  = 5;
	mVar[my_VolumeEffect] = 5;
	mVar[my_Leanguage]    = 0;//(0)ita - (1)eng
	mFile = "Config.txt";
}
myConfig::~myConfig()
{

}

bool myConfig::init()
{ 
	std::fstream load;
	load.open(mFile.c_str());
	
	if (load)
	{
		load.close();
		printf("File '%s' trovato.\n", mFile.c_str());
		return true;
	}
	else return false;
	
}

void myConfig::download()//                                  SISTEMAMI
{
	std::ifstream f(mFile.c_str());
	std::string s;
	int temp=-1;
	char shit[10];
	int i = 0;

	if (!f) {
		printf("Il file non esiste!");
		return;
	}

	while (f.good()) //fino a quando c'è qualcosa da leggere ..
	{
		//legge tutta la riga dal file e la mette nella variabile s
		getline(f, s);
		printf(" %s -> (",s.c_str());
		std::sscanf(s.c_str(),"%s = %d",shit,&temp);
		printf("%d)\n",temp);
		mVar[i++] = temp;
	}
	f.close(); //chiude il file

}

void myConfig::upload()
{

}

int myConfig::getResolution()
{
	return mVar[my_Resolution];
}
int myConfig::getVsynch()
{
	return mVar[my_Vshync];
}
int myConfig::getScreenMode()
{
	return mVar[my_ScreenMode];
}
int myConfig::getVolumeMusic()
{
	return mVar[my_VolumeMusic];
}
int myConfig::getVolumeEffect()
{
	return mVar[my_VolumeEffect];
}
int myConfig::getLeanguage()
{
	return mVar[my_Leanguage];
}

int myConfig::getWidth()
{
	int temp = 800;

	if (mVar[my_Resolution] == my_1280x720)
		temp = 1280;
	if (mVar[my_Resolution] == my_1600x900)
		temp = 1600;
	if (mVar[my_Resolution] == my_1920x1080)
		temp = 1920;
	if (mVar[my_Resolution] == my_800x450)
		temp = 800;
	if (mVar[my_Resolution] == my_800x600)
		temp = 800;


	return temp;
}
int myConfig::getHeight()
{
	int temp = 450;

	if (mVar[my_Resolution] == my_1280x720)
		temp = 720;
	if (mVar[my_Resolution] == my_1600x900)
		temp = 900;
	if (mVar[my_Resolution] == my_1920x1080)
		temp = 1080;
	if (mVar[my_Resolution] == my_800x450)
		temp = 450;
	if (mVar[my_Resolution] == my_800x600)
		temp = 600;

	return temp;
}
