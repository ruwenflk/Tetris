#include <SDL2/SDL.h>
#include "figures.h"
#include "gamefield.h"
#include "score.h"

#ifndef OUTPUT_H_
#define OUTPUT_H_

class out
{
private:
		//WENN MAN DIE HÖHE ÄNDERT, ÄNDERT SICH DIE GRÖßE DES GANZEN PROGRAMMS
		static const int height = 800;						//höhe des fenster, die grafische ausgabe passt sich dynamisch an
		static const int width = height*0.75;				//breite des fensters
		static const int size = height/20;					//größe der "quadrate" der figuren
		static const int numbersize = (width-(10*size))/25;	//größe der "quadrate" der punktezahlen
		static const Uint32 red = 	0xFF0000;				//rote farbe
		static const Uint32 white =	0xFFFFFF;				//weiße farbe
		static const Uint32 blue = 	0x0000FF;				//blaue farbe
		static const Uint32 black =	0x000000;				//schwarze farbe

		SDL_Window *window;							//pointer auf das SDL window, wird zur grafischen ausgabe benötigt
		SDL_Surface* screenSurface;					//pointer auf das SDL screensurface, wird zur grafischen ausgabe benötigt

public:
		out();

		//===grafische ausgabe des spielfelds und der figuren========//
		void draw(figure* fig_pointer, field* field_pointer);				//zeichnet das spielfeld mit der aktuellen figur
		void draw_next_fig(figure* fig_pointer, field* field_pointer);		//zeichnet die figur oben rechts im fenster (also die nächste figur)

		//===grafische ausgabe der punkte============================//
		void draw_score(points* pts_pointer);								//zeichnet die punktezahl

		//===fenster wird gelöscht -> speicher wird freigeräumt, bevor das programm beendet wird===//
		void quit_surface();

};

#endif
