#include "SDL2/SDL.h"
#include "figures.h"
#include "gamefield.h"
#include "output.h"
#include "score.h"

#ifndef CONTROL_H_
#define CONTROL_H_


class con
{
private:

	bool *quit;

	//==="zeitvariablen" für die "ticks"=======================//
	Uint32 time;
	Uint32 time2;
	double tick_time;

	//===pointer auf alle benötigten klassen==================//
	out* output;					//pointer auf die ausgabeklasse (zur grafischen ausgabe)
	figure* fig_pointer;			//pointer auf die figurklasse
	field* field_pointer;			//pointer auf die spielfeldklasse
	points* pts_pointer;			//pointer auf die punktezahlklasse

public:

	con(bool *quit);
	void quit_game();										//löscht das fenster und setzt in der main quit auf true


//===grafische ausgabe=================================//
	void draw();											//zeichnet das spielifeld
	void draw_next_fig_and_points();						//zeichnet die nächste figur

//===spielfeldmethoden=================================//
	void save_fig();										//speichern der figuren im spielfeld -> betroffene werte auf 1 setzen
	bool checkcollision(int directionX, int directionY);	//kollisionsabfrage
	int delete_lines();										//löschen von ganzen zeilen
	bool check_quit();

//===figurbewegungen===================================//
	void move_x(int x);										//links oder rechtsbewegung auf der x-achse
	void dash();											//sofortiges "nach unten fallen" der figur
	void offy_drop();										//einfaches "nach unten bewegen" auf der y-achse
	void turn_figure();										//drehen der figur
	void check_tick();										//methode für die "ticks"
};

#endif
