#ifndef GAMEFIELD_H_
#define GAMEFIELD_H_

class field
{
private:

	bool gamefield[10][20]; 			//Spielfeld als bool-array -> 0= leere felder , 1= besetzte felder

public:

	field();

	//===sets==========//
	void set_gamefield(int x, int y);	//für das speichern der figuren notwendig
	int delete_lines(int x);			//löscht volle zeilen im feld

	//===gets==========//
	int get_gamefield(int x, int y);
};

#endif
