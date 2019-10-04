#include <SDL.h>
#include <string>
#include <sstream>

#ifndef _mySave
#define _mySave 1

class mySave//unico salvataggio
{
	public:
		mySave();
		~mySave();
		void init(std::string file);
		void save();
		void addSave();
		void load();
		void deleteSave();
		void newSave();
		//int * returnSave();// saveData%d.save ogni salvataggio ha questa forma tanto vale che passo solo il numero

	private:
		SDL_RWops* mFile;
		std::string mNomeFile;
		bool mLoad;

};

#endif // !_mySave