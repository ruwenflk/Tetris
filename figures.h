#ifndef FIGURES_H_
#define FIGURES_H_

class figure
{
private:

	int x, x_next;  	//x und y wird im konstruktur zufällig ein wert zugewisen, damit zufällig figur geladen wird
	int y, y_next;		//
	int offy; 			//abstand der figur zur y-achse (von oben)
	int offx; 			//abstand der figur zur x-achse (von links)

public:

	figure();

	//===methoden zur initialisierung==========================================================================//
	void fig_init();   	//ruft alle initialisierungsmethoden auf
	void push_fig();	//die "neue" figur wird zur alten gemacht
	void rand_fig();	//generiert zufällig x und y, die benötigt werden, um eine figur aus dem array zu laden
	void init_off_y_x();//offy und offx werden der figur angepasst, sodass die figur "ganz oben" im feld startet


	//===sets=============//
	void set_y(int y);
	void set_offx(int x);
	void set_offy(int y);

	//===gets=============//
	int get_a(int x, int y);
	int get_b(int x, int y);
	int get_y();
	int get_offx();
	int get_offy();


};

#endif
