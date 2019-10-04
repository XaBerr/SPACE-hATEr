//libreria funzioni
#include "myUtility.h"

//funzioni locali

//main
int main(int argc, char* args[])
{
	printf("______________________________INIT\n");


	if (!initSDL())
	{
		printf("Errore SDL_Init():\n%s\n", SDL_GetError());
		getchar();
		return 1;
	}else printf("Inizializzazione SDL completata.\n");


	if (!initLauncher())
	{
		printf("Inizializzazione luncher non completata.\n");
		getchar();
		return 1;
	}else printf("Inizializzazione luncher completata.\n");


	if (!initGame())
		{
			printf("Inizializzazione gioco non completata.\n");
			getchar();
			return 1;
		}else printf("Inizializzazione gioco completata.\n");

	
	if (!loadMedia())
	{
		printf("File media non caricati!\n");
		getchar();
		return 1;
	}else printf("File media caricati.\n");


	printf("__________________________________\n");

	startGame();//piccolo adjustment
	
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Enable text input
	//SDL_StartTextInput();

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			
			//pool event
			quit = !(handleEvent(e));

		}
		
		engineMenu();		// Motori :D
		enginePhysics();	//
		engineGraphics();	//


		}

		//Disable text input
		//SDL_StopTextInput();
		

		//Free resources and close SDL
		close();
	
	

	return 0;
}
