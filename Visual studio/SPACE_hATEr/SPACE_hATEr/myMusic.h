#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>

#ifndef _myMusic
#define _myMusic 1



#define MY_MUSIC 1
#define MY_CHUNK 2

class myMusic
{
public:
	myMusic();
	~myMusic();
	bool loadMusicFromFile(std::string path, int format);
	void free();
	int getID();
	void resume();//riparti
	void play();//parti
	void pause();//metti in pausa
	void stop();//stoppa (halt)
	bool prova1(std::string path);
	bool prova2(std::string path);

private:
	int mID;
	Mix_Music *mMusic;
	Mix_Chunk *mChunk;
	int Music_format;
	bool mStart;
	bool mPause;

};

#endif // !_myMusic
