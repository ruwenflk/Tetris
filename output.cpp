#include "number_source.h"
#include "output.h"
#include <stdio.h>

//infos zum SDL_rect:
//das rect ist ein rechteck / quadrat, das man nachdem man es erstellt hat,  in das SDL window schreibt,
//folgende paramter sind enthalten (X-koordinate des fenster , Y-koordinate des fensters, vertikale größe in pixel, horizontale größe in pixel)
//
//SDLFillRect :
//füllt nun das window mit dem screensurface, dem rechteck und einer dazugehörigen farbe
// also:     SDLFillRect(fensteroberfläche, rechteck, farbe)
//
//das ganze wurde jetzt schon gezeichnet, aber noch nicht am monitor aktualisiert, dafür ist dann das
// SDL_UpdateWindowSurface(window) zuständig

out::out()
{
	//SDL initialisieren, falls ein Error auftaucht, wird ein "-1" zurückgegeben und man kann den gecatchten Error mit SDL_GetError() ausgeben.
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);   //Fenster wird erstellt, SDL_WINDOW_SHOWN sagt, dass das Fenster angezeigt wird (im Vordergrund), nachdem es erstellt wurde.
		if(window==NULL) //Falls das Fenster nicht erstellt werden konnte, wird auch hier der abgefangene Fehler ausgegeben.
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);	//Fensteroberfläche
		}
	}

		//===der teil im fenster rechts vom spielfeld wird hier weiß gefärbt===//
		SDL_Rect rect = {size*10, 0,width-(size*10), height};
		SDL_FillRect(screenSurface, &rect, white);
}
//=======grafische ausgabe der beiden figuren======================//
void out::draw(figure* fig_pointer, field* field_pointer)
{
	for (int y = 0; y < 20; y ++)
	{
		for (int x = 0; x < 10; x ++)
		{
			//hier wird nun jedes mal ein kleines quadrat erstellt, bis das spielfeld gezeichnet wurde, also 20x10 quadrate
			SDL_Rect rect = { x*size, y*size, size-1, size-1}; //durch das "-1" wird ein raster erzeugt
			bool drawfield = true;
			if (x >= fig_pointer->get_offx() && x < fig_pointer->get_offx() + 5 && y >= fig_pointer->get_offy() && y < fig_pointer->get_offy() + 5) //checken, ob bei der aktuellen position gerade eine figur ist
			{

				int temp = fig_pointer->get_a((y - fig_pointer->get_offy()),(x - fig_pointer->get_offx()));		//falls ja, figur zeichnen
				if (temp != 0)
				{
					SDL_FillRect(screenSurface, &rect, red);
					drawfield = false;											//sagt, dass das feld nicht gezeichnet werden soll an dieser stelle
				}
			}
			if (drawfield)
			{
				if (field_pointer->get_gamefield(x,y) == false)				//falls keine figur da ist, muss das feld gezeichnet werden.
				{
					SDL_FillRect(screenSurface, &rect, black);				//schwarz für leere felder
				}
				else
				{
					SDL_FillRect(screenSurface, &rect, blue);				//blau für besetzte felder
				}
			}
		}
	}
	SDL_UpdateWindowSurface(window);
}

void out::draw_next_fig(figure* fig_pointer, field* field_pointer)
{
	for(int y=0; y<5;y++)
	{
		for(int x=0; x<5; x++)
		{
			SDL_Rect rect = {x*size+(10*size), y*size+size, size-1, size-1};  //quadrate werden oben rechts im fenster gezeichnet
			if(fig_pointer->get_b(x,y)==false)
			{
				SDL_FillRect(screenSurface, &rect, white);					//analog zu oben
			}
			else
			{
				SDL_FillRect(screenSurface, &rect, blue);
			}
		}
	}
}

//========grafische ausgabe der punkte==========================================//
void out::draw_score(points* pts_pointer)          //zeichnen der punktezahl
{
	int x0=0;

	for(int p=0; p<6; p++)
	{

		for(int x=0; x<3; x++)
		{
			if(x0==p*3+(p-1))					//falls die letze spalte einer zahl erreicht wurde, wird danach ein eck freigelassen, damit die zahlen nicht so nah beieinander sind
				x0++;
			x0++;

			for(int y=0; y<5; y++)
			{
				SDL_Rect  rect = {size*10+x0*numbersize, size*10+y*numbersize, numbersize, numbersize };  //rechtecke werden rechts neben dem spielfeld gezeichnet
				if(number[pts_pointer->get_score(p)][y][x]==0)
				{
					SDL_FillRect(screenSurface, &rect, white);		//analog
				}
				else
				{
					SDL_FillRect(screenSurface, &rect, black);
				}

			}
		}
	}
}

//löschen des fensters
void out::quit_surface()
{
	SDL_Delay(1000);				//kleine verzögerung, bevor das fenster gelöscht wird
	SDL_DestroyWindow(window);		//fenster wird gelöscht
}
