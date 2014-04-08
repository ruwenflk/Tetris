//**********************************//
// TETRIS							//
// Author: Ruwen Fulek				//
//**********************************//

#include <SDL2/SDL.h>
#include "control.h"
#include <iostream>
using namespace std;


int main(int argc, char* args[])
{
	bool quit = false;


	con *control = new con(&quit);
	SDL_Event e;	//SDL event, wird z.b für die tastatureingabe benötigt


		//===================================================main loop========================================================//
		while (!quit)
		{
			try
			{
				control->check_tick();			//===überprüfen+ausführen der ticks ("drops" der figur auf y-aschse)

				while (SDL_PollEvent(&e) != 0)
				{
					//falls das fenster per "X" (oben rechts) geschlossen wird, wird SDL_QUIT "ausgelöst"
					if (e.type == SDL_QUIT)
						control->quit_game();

					//===Tastatureingabe==========================================//
					if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
							case SDLK_UP:				//drehen der figur
								control->turn_figure();
							break;

							case SDLK_LEFT:				//links-bewegung der figur
								control->move_x(-1);
							break;

							case SDLK_RIGHT:			//rechts-bewegung der figur
								control->move_x(1);
							break;

							case SDLK_DOWN:				//figur nach unten bewegen
								control->offy_drop();
							break;

							case SDLK_SPACE:			//figur bis zum boden fallen lassen
								control->dash();
							break;

							case SDLK_ESCAPE:			//alternative zum <"X" schließen>
								control->quit_game();
							break;
						}
					}
				}
			}
            catch(const char *str)
            {
                cout<<"Caught exception: "<< str <<endl;
            }

	}

	SDL_Quit(); //SDL beenden -> speicher freiräumen
	return 0;

}


