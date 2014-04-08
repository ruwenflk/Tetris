#ifndef SCORE_H_
#define SCORE_H_

class points
{
	private:

			int line_count[5];		//beinhaltet zahlen zur punkteberechnung, die davon abhängt, wie viele zeilen im spielfeld gelöscht wurden
			int score_arr[6];		//beinhaltet die einzelnen ziffern des aktuellen punktestands
			int score_int;			//aktueller punktestand als int-zahl

	public:

			points();
			void convert_score();			//teilt die punktezahl in ihre einzelnen ziffern und speichert sie in einem array

			//===gets===//
			int get_score(int a);

			//===sets===//
			void calc_score(int lines);		//berechnet die punktzahl mit hilfe der gelöschten zeilen des spielfelds und führt convert_score aus

};


#endif /* SCORE_H_ */
