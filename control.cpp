#include <SDL2/SDL.h>
#include "control.h"
#include "figures.h"
#include <iostream>
using namespace std;

//===Konstruktor==========================//
con::con(bool *quit)
{
	this->quit=quit; //pointer auf quit in der main
	//===für das spiel benötigten objekte erstellen================//
	fig_pointer = new figure();
	field_pointer = new field();
	output = new out();
	pts_pointer = new points();

	//===zeitvariablen für die "ticks" initialisieren===========//
	time = SDL_GetTicks();
	time2 = SDL_GetTicks();
	tick_time = 350;

	//die ""nächste figur" und punkte einmalig aus konstruktor zeichnen lassen, später wird das gemacht, wenn eine figur gespeichert wird
	con::draw_next_fig_and_points();
}

void con::quit_game()
{
	output->quit_surface();															//wird diese methode aufgerufen, wird das spiel beendet und speicher freigeräumt
	*quit=true;
}

//===grafische ausgabe===============================================//
void con::draw()
{
	output->draw(fig_pointer,field_pointer);										//Spielfeld in der draw methode der output klasse zeichnen lassen
}

void con::draw_next_fig_and_points()
{
	output->draw_next_fig(fig_pointer, field_pointer);								//die "nächste figur" in der draw_next_fig methode der output klasse zeichnen lassen
	output->draw_score(pts_pointer);												//den punktestand in der draw_score methode der output klasse zeichnen lassen
}

//===feldmethoden====================================================//
void con::save_fig()																					//Figur im Spielfeld speichern
{																										//
	for(int y=0; y<5; y++)																				//
	{																									//
		for(int x=0; x<5; x++)																			//
		{																								//
																										//
			if (fig_pointer->get_a(y,x) == 1)															//
			{																							//
				field_pointer->set_gamefield(fig_pointer->get_offx()+x, fig_pointer->get_offy()+y);		//
			}																							//
		}																								//
	}																									//
//nachtdem die figur gespeichert wurde, werden automatisch weitere schritte eingeleitet
	if(!check_quit())														//prüfuen, ob das spiel vorbei ist
	{																		//
		pts_pointer->calc_score(delete_lines());							//gucken, ob zeilen gelöscht werden können und wenn ja, löschen. die löschfunktion gibt die anzahl an gelöschten zeilen zurück und wird über die control klasse an die score klasse weitergegeben, damit die punkte berechnet werden können
		fig_pointer->fig_init();											//neue figur in der figurklasse initialisieren, außerdem werden dort automatisch weitere methoden ausgeführt, die zum initialisieren notwendig sind
		tick_time = tick_time * 0.99;										//die "tick_time" um 1 prozent verringern. das spiel soll ja immer schneller werden
		draw_next_fig_and_points();											//diese methode ruft zwei methoden in der ausgabeklasse auf, eine zum zeichnen der neuen figur, die eben initialisiert wurde und eine, die den punktestand ausgibt
		draw();																//Spielfeld Zeichnen
	}																		//
	else quit_game();
}

bool con::checkcollision(int directionX, int directionY)																			//KOLLISIONSABFRAGE
{
	for(int y=0; y<5; y++)
	{
		for(int x=0; x<5; x++)
		{

			if (fig_pointer->get_a(y,x) == 1)
			{
				if (fig_pointer->get_offy() +y >= 19)																				//Checken, ob die figur das untere ende erreicht
					return true;
				if (fig_pointer->get_offx() +x+directionX >= 10 || fig_pointer->get_offx() +x + directionX < 0)						//Checken, ob die figur das horizontale ende links oder rechts erreicht ist
					return true;
				if ((field_pointer->get_gamefield(fig_pointer->get_offx()+x+directionX,fig_pointer->get_offy()+y+directionY)) == 1) //Checken, ob die figur mit mit gespeicherten figuren auf dem spielfeld kollidiert
					return true;
			}
		}
	}
	return false;
}

																									//																															//

int con::delete_lines()
{																						//führt die methode delete lines in der spielfeldklasse aus	und übergibt off_y als parameter
	return field_pointer->delete_lines(fig_pointer->get_offy());						//,damit das spielfeld nur 5 zeilen zu checken brauch
}																						//und nicht alle 20

bool con::check_quit()
{																	//prüft, ob die letzte zeile erreicht wurde	und somit das spiel beendet werden soll
	int sum=0;														//und somit das spiel beendet werden soll
	for(int x=0; x<10; x++)											//
	{																//
		sum += field_pointer->get_gamefield(x,0);					//
	}																//
																	//
	if(sum>0)														//
		return true;												//
	else															//
		return false;												//
}

//===figurbewegungen=================================================//
void con::move_x(int x)												//figur links oder rechts bewegen
{
	if (!checkcollision(x,0))
		fig_pointer->set_offx(fig_pointer->get_offx()+x);
	draw();
}

void con::dash()													//figur fallen lassen
{
	bool stop=false;
	while(!stop)
	{
		if(checkcollision(0,1))										//
			stop=true;												//die figur immer weiter um eins fallen lassen, bis die killisionsabfrage ein ja zurückgibt
		else
			fig_pointer->set_offy(fig_pointer->get_offy()+1);
	}
	save_fig();
	draw();
}

void con::offy_drop()												//figur nach unten bewegen
{
	if (!checkcollision(0,1))
		fig_pointer->set_offy(fig_pointer->get_offy()+1);
	draw();
}



void con::turn_figure()												//figur drehen
{																	//
	int oldY = fig_pointer->get_y();								//
	if (oldY==3)													//
	{																//
		fig_pointer->set_y(0);										//
	}																//
	else															//
		fig_pointer->set_y(oldY+1);									//
																	//
																	//
	if (checkcollision(0,0))										//und dann eine kollisionsabfrage gemacht
	{																//kollidiert die gedrehte figur, wird sie zurückgedreht
		fig_pointer->set_y(oldY);									//
	}																//
	draw();															//
}																	

void con::check_tick()
{
	time2 = SDL_GetTicks();															//time 2 auf die aktuelle zeit setzen
																					//
	if((time2-time)>tick_time)														//gucken ob die differenz größer als die tick_time ist
	{																				//wenn ja,
		if (!checkcollision(0,1))													//
		{																			//kollisionscheck für die y achse machen
			offy_drop();															//
		}																			//
		else																		//
		{																			//falls kollision
			save_fig();																//die save_fig methode speichert die figur und leitet alle weiteren schritte ein zur neuinitialisierung
		}																			//
																					//
		time = SDL_GetTicks();														//die erste zahl auf die aktuelle zeit setzen
	}
}


