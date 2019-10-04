#include "myMusic.h"

myMusic::myMusic()
{
	mID = 0;
	mMusic = NULL;
	mChunk = NULL;
	Music_format = 0;
	mStart = false;
	mPause = false;
}

myMusic::~myMusic()
{
	if (Music_format == MY_MUSIC)
		Mix_FreeMusic(mMusic);
	
	if (Music_format == MY_CHUNK)
		Mix_FreeChunk(mChunk);

	mID = 0;
	mMusic = NULL;
	mChunk = NULL;
	Music_format = 0;
	mStart = false;
	mPause = false;
}

bool myMusic::loadMusicFromFile(std::string path, int format)
{
	if ((format != 1) && (format != 2))
		return false;

	bool success = true;
	Music_format = format;

	if (format == 1)
	{
		mMusic = Mix_LoadMUS(path.c_str());
		if (mMusic == NULL)
		{
			printf("Fallito caricamento musica. Errore:\n%s\n", Mix_GetError());
			success = false;
		}else printf("Caricamento musica riuscito.\n");
	}
	else
	{
		mChunk = Mix_LoadWAV(path.c_str());
		if (mChunk == NULL)
		{
			printf("Fallito caricamento chunk. Errore:\n%s\n", Mix_GetError());
			success = false;
		}else printf("Caricamento chunk riuscito.\n");
	}

	return success;
}

void myMusic::play()
{
	if ((Music_format == MY_MUSIC)&&(!mStart))
	{
		Mix_PlayMusic(mMusic, -1);
		mStart = true;
		mPause = false;
	}
	if (Music_format == MY_CHUNK)
		Mix_PlayChannel(-1, mChunk, 0);
}

void myMusic::pause()
{
	if (Music_format == MY_CHUNK)
		return;
	if ((mStart)&&(!mPause))
	{
		Mix_PauseMusic();
		mPause = true;
	}
}

void myMusic::resume()
{
	if (Music_format == MY_CHUNK)
		return;
	if ((mStart)&&(mPause))
	{
		Mix_ResumeMusic();
		mPause = false;
	}
}

void myMusic::stop()
{
	if (Music_format == MY_CHUNK)
		return;
	if (mStart)
	{
		Mix_HaltMusic();
		mStart = false;
		mPause = false;
	}
}