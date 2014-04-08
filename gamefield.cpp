#include "gamefield.h"

field::field()
{
	for (int j = 0;j < 10;j++)
	{
		for (int i = 0; i < 20; i++)
		{
			gamefield[j][i] = false;  				//ganzes spielfeld auf 0 setzen
		}
	}
}

//===sets==============================//

void field::set_gamefield(int x, int y)
{
	gamefield[x][y]=1;
}

int field::delete_lines(int x)
{
	int sum;
	int number_lines=0;

	for(int y=x; y<x+5 && y<20; y++)
	{
		sum=0;
		for(int x=0; x<10; x++)
		{
			sum += gamefield[x][y];					//berechnet die summe der aktuellen zeile
		}

		if(sum==10)
		{
			number_lines++;
			for(int y0=y; y0>0; y0--)
			{
				for(int x0=0; x0<10; x0++)
				{
					gamefield[x0][y0] = gamefield[x0][y0-1];	//lässt jede zeile um eins nach unten fallen
				}
			}
		}
	}
	return number_lines;
}

//===gets=============================//

int field::get_gamefield(int x, int y)
{
	return gamefield[x][y];
}



