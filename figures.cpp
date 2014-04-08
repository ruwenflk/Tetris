#include <iostream>
#include <cstdlib>
#include "figures.h"
#include "fig_source.h"


//===Konstuktor=====//
figure::figure()
{
	srand (time(NULL));  //initialisiert den zufallsgenerator mit der uhrzeit (sonst würde die reihenfolge der figuren immer gleich sein)
			x = rand() % 5;  //die erste figur soll kein N oder N-gespiegelt sein, da es "unschön" ist, so anzufangen.
			y = rand() % 4;

	init_off_y_x();
	rand_fig();

}

//===methoden zur initialisierung==================//
void figure::fig_init()
{
	push_fig();
	rand_fig();
	init_off_y_x();
}

void figure::push_fig()
{
	x = x_next;
	y = y_next;
}


void figure::rand_fig()
{
	srand (time(NULL));  										//initialisiert den zufallsgenerator mit der uhrzeit (sonst würde die reihenfolge der figuren immer gleich sein)
		x_next = rand() % 7;
		y_next = rand() % 4;
}

void figure::init_off_y_x()
{																//diese methode überprüft, wo "offy" den startwert hat, es ist nämlich möglich, dass die ersten beiden
	offx = 3;													//zeilen im figurarray frei sind oder nur eine und dann muss offy angepasst werden.
	offy = 0;

	int sum1=0;
	int sum2=0;

	for(int i=0;i<5;i++)
	{
		sum1 += (figures[this->x][this->y][i][0]);				//die summe der ersten zeile prüfen
		sum2 += (figures[this->x][this->y][i][1]);				//die summe der zweiten zeile prüfen
	}

	if(sum1==0)
	{
		offy = -1;
		if(sum2==0)
		{
			offy = -2;
		}
	}
}


//===sets==========================================//
void figure::set_y(int y)
{
	this->y=y;
}

void figure::set_offx(int x)
{
	offx=x;
}

void figure::set_offy(int y)
{
	offy=y;
}

//===gets==========================================//
int figure::get_a(int y, int x)
{
	return figures[this->x][this->y][x][y];
}

int figure::get_b(int x, int y)
{
	return figures[this->x_next][this->y_next][x][y];
}

int figure::get_y()
{
	return y;
}

int figure::get_offx()
{
	return offx;
}

int figure::get_offy()
{
	return offy;
}


