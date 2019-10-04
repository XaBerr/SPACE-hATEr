#include "..\myTexture.h"
#include <SDL.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

#define DIM_MAP_X 1920*2
#define DIM_MAP_Y 1080*2
#define DIM_BLK_X 1920
#define DIM_BLK_Y 1080

#ifndef _myMap
#define _myMap 1

class myMap
{
public:
	myMap();
	~myMap();
	bool downLoadTexture(float x, float y);
	void render();
	void position(float x, float y);
	void loadStructure(std::string file);//da map.txt
	void uploadSave();//da salvataggi
	void downloadSave();//a salvataggi
	bool isTextureLoad();//mload
	void move(float x, float y);
	void coord4v(float x, float y, float xy[8]);
	

private:
	myTexture mBotLeft;
	myTexture mTopLeft;
	myTexture mTopRight;
	myTexture mBotRight;
	float mX;//coordinate mondo
	float mY;//coordinate mondo
	bool mLoad;
	//---------------------------variabili funzione load texture
	//coordinate dei 4 angoli della camera
	float mXY[8];
	float mNewXY[8];

};


#endif // !_myMap
