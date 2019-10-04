
#include <SDL.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

#ifndef _myConfig
#define _myConfig 1

#define my_800x600   0//1.333
#define my_800x450   1//1.777
#define my_1280x720  2//1.777
#define my_1600x900  3//1.777
#define my_1920x1080 4//1.777

//                       default  info  
#define my_Resolution   0//(3)
#define my_Vshync       1//(0)    1 true 0 false
#define my_ScreenMode   2//(0)    full - windowed - deskWindowed
#define my_VolumeMusic  3//(5)
#define my_VolumeEffect 4//(5)
#define my_Leanguage    5//(0)    0 ita - 1 eng


class myConfig
{
	public:
		myConfig();
		~myConfig();
		bool init();
		void download();
		void upload();
		int getResolution();
		int getVsynch();
		int getScreenMode();
		int getVolumeMusic();
		int getVolumeEffect();
		int getLeanguage();
		int getWidth();
		int getHeight();

	private:
		int mVar[6];
		std::string mFile;

};

#endif // !_myConfig