#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

char A[9][9]{
	{'8','r','h','b','q','k','b','h','r'},
	{'7','p','p','p','p','p','p','p','p'},
	{'6','0','0','0','0','0','0','0','0'},
	{'5','0','0','0','0','0','0','0','0'},
	{'4','0','0','0','0','0','0','0','0'},
	{'3','0','0','0','0','0','0','0','0'},
	{'2','P','P','P','P','P','P','P','P'},
	{'1','R','H','B','Q','K','B','H','R'},
	{' ','A','B','C','D','E','F','G','H'}
};
char A2[9][9]{ //копия основного двумерного массива для цикличности ввода в случае шаха
	{'8','r','h','b','q','k','b','h','r'},
	{'7','p','p','p','p','p','p','p','p'},
	{'6','0','0','0','0','0','0','0','0'},
	{'5','0','0','0','0','0','0','0','0'},
	{'4','0','0','0','0','0','0','0','0'},
	{'3','0','0','0','0','0','0','0','0'},
	{'2','P','P','P','P','P','P','P','P'},
	{'1','R','H','B','Q','K','B','H','R'},
	{' ','A','B','C','D','E','F','G','H'}
};
/*	двумерные массивы for_black_figures и for_white_figures 
	предназначены для функции шаха(check_for_kings) и основной функции короля(king_move);
	после каждого хода информация в соответствующей матрице меняется	
	for_black_figures определяет местонахождение всех чёрных фигур и их возможные ходы
	for_white_figures определяет местонахождение всех белых фигур и их возможные ходы	
	P.S. в двумерных массивах добавлена рамка из цифр и букв	*/
char for_black_figures[9][9]{ 
	{'8','0','0','0','0','0','0','0','0'},
	{'7','0','0','0','0','0','0','0','0'},
	{'6','0','0','0','0','0','0','0','0'},
	{'5','0','0','0','0','0','0','0','0'},
	{'4','0','0','0','0','0','0','0','0'},
	{'3','0','0','0','0','0','0','0','0'},
	{'2','0','0','0','0','0','0','0','0'},
	{'1','0','0','0','0','0','0','0','0'},
	{' ','A','B','C','D','E','F','G','H'}
};
char for_white_figures[9][9]{
	{'8','0','0','0','0','0','0','0','0'},
	{'7','0','0','0','0','0','0','0','0'},
	{'6','0','0','0','0','0','0','0','0'},
	{'5','0','0','0','0','0','0','0','0'},
	{'4','0','0','0','0','0','0','0','0'},
	{'3','0','0','0','0','0','0','0','0'},
	{'2','0','0','0','0','0','0','0','0'},
	{'1','0','0','0','0','0','0','0','0'},
	{' ','A','B','C','D','E','F','G','H'}
};
vector <int> numbers_for_bishop = {2, 8, 18, 32, 50, 72, 98}; // для проверки на диагональ слона
string up = "PRHBQK0"; // для проверки на взятие своих фигур
string down = "prhbqk0";
int determine = 0; //счётчик для определения противника. Белые фигуры(Верхний регистр) - нечётные; чёрные фигуры(нижний регистр) - чётные

void rearranging(int i, int j, int new_i, int new_j, string arr){ //перестановка фигуры
	if (arr == "A1"){ //перестановка для главного двумерного массива
		A[new_i][new_j] = A[i][j];
		A[i][j] = '0';		
	}
	else if (arr == "A2"){//перестановка для копии
		A2[new_i][new_j] = A2[i][j];
		A2[i][j] = '0';		
	}

}
void print(){ //функция вывода главного массива с дополнительной рамкой цифр и букв
		cout << "\n     A B C D E F G H" << endl;
		for (int i = 0; i < 9; i++) {
			cout << "  ";
        	for (int j = 0; j < 9; j++) cout << setw(2) << A[i][j];
			if (i != 8) cout << " " << 8 - i;
     		cout << endl;
		}
		cout << endl;
}
int switch_char (char ch, bool &flag){ 	//определяет j в матрице (столбец)
        int j;
		switch (ch){
			case 'A':{
				j = 1;
				break;
			}
			case 'a':{
				j = 1;
				break;
			}
			case 'B':{
				j = 2;
				break;
			}
			case 'b':{
				j = 2;
				break;
			}
			case 'C':{
				j = 3;
				break;
			}
			case 'c':{
				j = 3;
				break;
			}
			case 'D':{
				j = 4;
				break;
			}
			case 'd':{
				j = 4;
				break;
			}
			case 'E':{
				j = 5;
				break;
			}
			case 'e':{
				j = 5;
				break;
			}
			case 'F':{
				j = 6;
				break;
			}
			case 'f':{
				j = 6;
				break;
			}
			case 'G':{
				j = 7;
				break;
			}
			case 'g':{
				j = 7;
				break;
			}
			case 'H':{
				j = 8;
				break;
			}
			case 'h':{
				j = 8;
				break;
			}
			default:{
				flag = 0;
				cout << "wrong checkerboard cage.(char)" << endl;
				break;
			}
		}
    return j;
}
int switch_int (char int_, bool &flag){ // определяет i в матрице (строка) 
    int i;
	switch (int_){
		case '1':{
			i = 7;
			break;
		}
		case '2':{
			i = 6;
			break;
		}
		case '3':{
			i = 5;
			break;
		}
		case '4':{
			i = 4;
			break;
		}
		case '5':{
			i = 3;
			break;
		}
		case '6':{
			i = 2;
			break;
		}
		case '7':{
			i = 1;
			break;
		}
		case '8':{
			i = 0;
			break;
		}
		default:{
			flag = 0;
			cout << "wrong checkerboard cage.(int)" << endl;
			break;
		}
	}
    return i;
}

struct chess_figures{

	bool define_figure(int i, int j, int new_i, int new_j){ 
			/*определяет тип фигуры для последущего вызова конкретной функции. 
			Если ход возможен, то возвращает true; 
			если ход невозможен или клетка пуста, то - false */
			bool flag = false;
			if (A[i][j] == 'P' || A[i][j] == 'p') { return flag = pawn_move(i, j, new_i, new_j); }
			if (A[i][j] == 'R' || A[i][j] == 'r') { return flag = rook_move(i, j, new_i, new_j); }
			if (A[i][j] == 'B' || A[i][j] == 'b') { return flag = bishop_move(i, j, new_i, new_j); }
			if (A[i][j] == 'H' || A[i][j] == 'h') { return flag = horse_move(i, j, new_i, new_j); }
			if (A[i][j] == 'K' || A[i][j] == 'k') { return flag = king_move(i, j, new_i, new_j); }
			if (A[i][j] == 'Q' || A[i][j] == 'q') { return flag = queen_move(i, j, new_i, new_j); }
			return flag;
	}
	//функции, которые проверяют, правильно ли ходят фигуры
	bool pawn_move(int i, int j, int new_i, int new_j){ //без учёта взятия на проходе
		if (!(determine % 2)){// black
	 		if (A[i][j] != 'p') return false; // проверка на регистр
			if (j == new_j){
				if (new_i == i+1) return true;
				if ((new_i == i + 2 && i == 1)&& A[i+1][j] == '0') return true;

			}
			else if (new_i == i + 1 && A[new_i][new_j] != '0'){
				if (new_j == j + 1 || new_j == j - 1){
					for (int k = 0; k < up.size(); k++){
						if (A[new_i][new_j] == up[k]) return true;
					}
				}
				else return false;
			}
			}
		if (determine % 2){ // WHITE
			if (A[i][j] != 'P') return false; // проверка на регистр
			if (j == new_j){
				if (new_i == i-1 ) return true;
				if ((new_i == i - 2 && i == 6) && A[i-1][j] == '0') return true;
			}
			else if (new_i == i - 1 && A[new_i][new_j] != '0'){
				if (new_j == j + 1 || new_j == j - 1){
					for (int k = 0; k < down.size(); k++){
						if (A[new_i][new_j] == down[k]) return true;
					}
				}
				else return false;
			}
			}
		return false;
	}
	bool rook_move(int i, int j, int new_i, int new_j) {
			if (!(determine % 2)){//black
				if (A[i][j] != 'r') return false; // проверка на регистр
				if (new_j == j){  //ход по вертикали
					if (i > new_i){
						for (int h = i - 1; h > new_i; h-- ) if (A[h][new_j] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
					}
					else if (i < new_i){
						for (int h = i + 1; h < new_i; h++) if (A[h][new_j] != '0') return false;//проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
					} 
				}
				if (new_i == i){ //ход по горизонтали
					if (j > new_j){
						for (int h = j - 1; h > new_j; h--) if (A[new_i][h] != '0') return false;//проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
					}
					else if (j < new_j){
						for (int h = j + 1; h < new_j; h++) if (A[new_i][h] != '0') return false;//проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
					}	
				
				}
			}
			if (determine % 2){ // WHITE
				if (A[i][j] != 'R') return false;// проверка на регистр
				if (new_j == j){ //ход по вертикали
					if (i > new_i){
						for (int h = i - 1; h > new_i; h-- ) if (A[h][new_j] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
					}
					else if (i < new_i){
						for (int h = i + 1; h < new_i; h++) if (A[h][new_j] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
					} 
				}
				if (new_i == i){ // ход по горизонтали
					if (j > new_j){
						for (int h = j - 1; h > new_j; h--) if (A[new_i][h] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
					}
					else if (j < new_j){
						for (int h = j + 1; h < new_j; h++) if (A[new_i][h] != '0') return false; //проверяется есть ли фигуры, мешающие перестановке
						for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
					}	
				
				}
			}
			return false;
	}
	bool bishop_move(int i, int j, int new_i, int new_j) {
		bool flag = false;
		int square = (i - new_i)*(i - new_i) + (j-new_j)*(j-new_j);
		for (int m = 0; m < numbers_for_bishop.size(); m++){ //проверка на возможность хода по диагонали
			if (square == numbers_for_bishop[m]){
				flag = true; 
				break;
			}
		}
		if (flag){
			if (j < new_j){ // проверка на наличие фигур, мешающих перестановке
				if (i > new_i){
					for (int ii = i - 1,  jj = j + 1; ii > new_i, jj < new_j; ii--, jj++){
						if (A[ii][jj] != '0') return false;
					}
				}
				if (i < new_i){
					for (int ii = i + 1,  jj = j + 1; ii < new_i, jj < new_j; ii++, jj++){
						if (A[ii][jj] != '0') return false;
					}				
				}
			}
			else if (j > new_j){// проверка на наличие фигур, мешающих перестановке
				if (i > new_i){
					for (int ii = i - 1, jj = j - 1; ii > new_i, jj > new_j; ii-- , jj--){
						if (A[ii][jj] != '0') return false;
					}
				}
				if (i < new_i){
					for (int ii = i + 1, jj = j - 1; ii < new_i, jj > new_j; ii++ , jj--){
						if (A[ii][jj] != '0') return false;
					}
				}
			}

				if (!(determine % 2)){//black
					if (A[i][j] != 'b') return false; // проверка регистра
						for (int k = 0; k < up.size(); k++) 
							if (A[new_i][new_j] == up[k]) return true;
				}
				if(determine % 2) { //WHITE
					if (A[i][j] != 'B') return false; // проверка регистра
						for (int k = 0; k < down.size(); k++) 
							if (A[new_i][new_j] == down[k]) return true;
				}
		}
		return false;
	}
	bool horse_move(int i, int j, int new_i, int new_j) {
		if (!(determine % 2)){// black
			if (A[i][j] != 'h') return false; // проверка регистра
			bool flag = false;
			for (int k = 0; k < up.size(); k++){ // проверка на взятие своих фигур
					if (A[new_i][new_j] == up[k]){ 
						flag = true;
						break;
					}
				}
			if (flag){
				if (new_j == j + 1){
					if (new_i == i - 2) return true;
					if (new_i == i + 2) return true;
				}
				if (new_j == j - 1){
					if (new_i == i - 2) return true;
					if (new_i == i + 2) return true;
				}
				if (new_j == j + 2){
					if (new_i == i + 1) return true;
					if (new_i == i - 1) return true;
				}
				if (new_j == j - 2){
					if (new_i == i + 1) return true;
					if (new_i == i - 1) return true;
				}
				return false;
			}
			else return false;
			
		}
		if (determine % 2){ //WHITE
			if (A[i][j] != 'H') return false; // проверка регистра
			bool flag = false;
			for (int k = 0; k < down.size(); k++){ // проверка на взятие своих фигур
					if (A[new_i][new_j] == down[k]){
						flag = true;
						break;
					}
				}
			if (flag){
				if (new_j == j + 1){
					if (new_i == i - 2) return true;
					if (new_i == i + 2) return true;
				}
				if (new_j == j - 1){
					if (new_i == i - 2) return true;
					if (new_i == i + 2) return true;
				}
				if (new_j == j + 2){
					if (new_i == i + 1) return true;
					if (new_i == i - 1) return true;
				}
				if (new_j == j - 2){
					if (new_i == i + 1) return true;
					if (new_i == i - 1) return true;
				}
				return false;
			} 
			else return false;
		}
		return false;
	}
	bool king_move(int i, int j, int new_i, int new_j) {
        if (!(determine%2)){ //black
			if (for_white_figures[new_i][new_j] == '1') return false; // проверка на битую клетку
            if (A[i][j] != 'k') return false; // проверка на регистр
            if (new_j == j){
	        		if (new_i == i + 1){
	        			if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
	        		}
	        		if (new_i == i - 1){
	        			if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;			
	        		}
	        		return false;
	        	}
	        if (new_j == j + 1){
	        	if (new_i == i + 1){
	        		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
	        	}
	        	if (new_i == i - 1){
	        		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
	        	}
	        	if (new_i == i){
	        		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
	        	}
	        	return false; 
	            }
	        if (new_j == j - 1){
		    	if (new_i == i + 1){
		    		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
		    	}
		    	if (new_i == i - 1){
		    		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
		    	}
		    	if (new_i == i){
		    		if (!(determine%2)) for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
		    	}
		    	return false; 
                }
            }
        
        if (determine%2){ // WHITE
			if (for_black_figures[new_i][new_j] == '1') return false;// проверка на битую клетку
            if (A[i][j] != 'K') return false; // проверка регистра
 		    if (new_j == j){
		    	if (new_i == i + 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	if (new_i == i - 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;				
		    	}
		    	return false; 
		    }
		    if (new_j == j + 1){
		    	if (new_i == i + 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true; 
		    	}
		    	if (new_i == i - 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	if (new_i == i){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	return false; 
		    }
		    if (new_j == j - 1){
		    	if (new_i == i + 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	if (new_i == i - 1){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	if (new_i == i){
		    		if (determine%2) for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
		    	}
		    	return false; 
		    }           
            }
        return false;
    }
	bool queen_move(int i, int j, int new_i, int new_j) {
    	if (!(determine%2)){ // black
        	if (A[i][j] != 'q') return false; // проверка на регистр
        	if (true){ //проверка на ход ладьи
        	    if (new_j == j){ // ход по вертикали
				if (i > new_i){
					for (int h = i - 1; h > new_i; h-- ) if (A[h][new_j] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке(вертикаль)
					for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
				}
				else if (i < new_i){
					for (int h = i + 1; h < new_i; h++) if (A[h][new_j] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке(вертикаль)
					for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
				} 
    			}
    			if (new_i == i){ // ход по горизонтали
				if (j > new_j){
					for (int h = j - 1; h > new_j; h--) if (A[new_i][h] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке
					for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true;
				    }
				else if (j < new_j){
					for (int h = j + 1; h < new_j; h++) if (A[new_i][h] != '0') return false;  // проверяется есть ли фигуры, мешающие перестановке
					for (int k = 0; k < up.size(); k++) if (A[new_i][new_j] == up[k]) return true; 
				    }	

    			}            
    	    }
    	    if (true){ //проверка на ход слона
 				bool flag = false;
				int square = (i - new_i)*(i - new_i) + (j-new_j)*(j-new_j);
				for (int m = 0; m < numbers_for_bishop.size(); m++){ //проверка на возможность хода по диагонали
					if (square == numbers_for_bishop[m]){
						flag = true; 
						break;
					}
				}
				if (flag){
					if (j < new_j){ // проверка на наличие фигур, мешающих перестановке
						if (i > new_i){
							for (int ii = i - 1,  jj = j + 1; ii > new_i, jj < new_j; ii--, jj++){
								if (A[ii][jj] != '0') return false;
							}
						}
						if (i < new_i){
							for (int ii = i + 1,  jj = j + 1; ii < new_i, jj < new_j; ii++, jj++){
								if (A[ii][jj] != '0') return false;
							}				
						}
					}
					else if (j > new_j){// проверка на наличие фигур, мешающих перестановке
						if (i > new_i){
							for (int ii = i - 1, jj = j - 1; ii > new_i, jj > new_j; ii-- , jj--){
								if (A[ii][jj] != '0') return false;
							}
						}
						if (i < new_i){
							for (int ii = i + 1, jj = j - 1; ii < new_i, jj > new_j; ii++ , jj--){
								if (A[ii][jj] != '0') return false;
							}
						}
					}

						if (!(determine % 2)){//black
							if (A[i][j] != 'q') return false; // проверка регистра
								for (int k = 0; k < up.size(); k++) 
									if (A[new_i][new_j] == up[k]) return true;
						}
						if(determine % 2) { //WHITE
							if (A[i][j] != 'Q') return false; // проверка регистра
								for (int k = 0; k < down.size(); k++) 
									if (A[new_i][new_j] == down[k]) return true;
						}
				}
    			    return false;
    		}
		}
    	if (determine%2){ // WHITE
        	if (A[i][j] != 'Q') return false; // проверка на регистр
        	if (true){ //проверка на ход ладьи
        	    if (new_j == j){ // ход по вертикали
				    if (i > new_i){
				    	for (int h = i - 1; h > new_i; h-- ) if (A[h][new_j] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке(вертикаль)
				    	for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
				    }
				    else if (i < new_i){
				    	for (int h = i + 1; h < new_i; h++) if (A[h][new_j] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке(вертикаль)
				    	for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true;
				    } 
    			}
    			if (new_i == i){ // ход по горизонтали
				    if (j > new_j){
				    	for (int h = j - 1; h > new_j; h--) if (A[new_i][h] != '0') return false; // проверяется есть ли фигуры, мешающие перестановке
				    	for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] ==down[k]) return true;
				        }
				    else if (j < new_j){
				    	for (int h = j + 1; h < new_j; h++) if (A[new_i][h] != '0') return false;  // проверяется есть ли фигуры, мешающие перестановке
				    	for (int k = 0; k < down.size(); k++) if (A[new_i][new_j] == down[k]) return true; 
				        }	
    			}            
        	}
    	    if (true){ //проверка на ход слона
 				bool flag = false;
				int square = (i - new_i)*(i - new_i) + (j-new_j)*(j-new_j);
				for (int m = 0; m < numbers_for_bishop.size(); m++){ //проверка на возможность хода по диагонали
					if (square == numbers_for_bishop[m]){
						flag = true; 
						break;
					}
				}
				if (flag){
					if (j < new_j){ // проверка на наличие фигур, мешающих перестановке
						if (i > new_i){
							for (int ii = i - 1,  jj = j + 1; ii > new_i, jj < new_j; ii--, jj++){
								if (A[ii][jj] != '0') return false;
							}
						}
						if (i < new_i){
							for (int ii = i + 1,  jj = j + 1; ii < new_i, jj < new_j; ii++, jj++){
								if (A[ii][jj] != '0') return false;
							}				
						}
					}
					else if (j > new_j){// проверка на наличие фигур, мешающих перестановке
						if (i > new_i){
							for (int ii = i - 1, jj = j - 1; ii > new_i, jj > new_j; ii-- , jj--){
								if (A[ii][jj] != '0') return false;
							}
						}
						if (i < new_i){
							for (int ii = i + 1, jj = j - 1; ii < new_i, jj > new_j; ii++ , jj--){
								if (A[ii][jj] != '0') return false;
							}
						}
					}

						if (!(determine % 2)){//black
							if (A[i][j] != 'q') return false; // проверка регистра
								for (int k = 0; k < up.size(); k++) 
									if (A[new_i][new_j] == up[k]) return true;
						}
						if(determine % 2) { //WHITE
							if (A[i][j] != 'Q') return false; // проверка регистра
								for (int k = 0; k < down.size(); k++) 
									if (A[new_i][new_j] == down[k]) return true;
						}
				}
    			    return false;
    		}
        	return false;
    	}
    	return false;
	}

	void changes_for_white_figures(string array){ // поиск белых фигур
		//функция предназначена для заполнения битыми клетками двумерного массива for_white_figures
		if (array == "A1"){//бегает по главному двумерному массиву и ищет белые фигуры
			for (int ii = 0; ii < 8; ii++){ 
				for (int jj = 1; jj < 9; jj++){
					for (int counter_for_char = 0; counter_for_char < up.size() - 1; counter_for_char++){ //(up.size() - 1) т.к. up и down включают в себя 0, находящийся в конце массива
						if (A[ii][jj] == up[counter_for_char]) define_for_changes(A[ii][jj], ii, jj, 'w'); //'w' - цвет
					}
				}
			}
		}
		if (array == "A2"){//бегает по копии двумерного массива и ищет белые фигуры(предназначено для отслеживания правильности хода, который уведёт короля от шаха)
			for (int ii = 0; ii < 8; ii++){ 
				for (int jj = 1; jj < 9; jj++){
					for (int counter_for_char = 0; counter_for_char < up.size() - 1; counter_for_char++){ //(up.size() - 1) т.к. up и down включают в себя 0, находящийся в конце массива
						if (A2[ii][jj] == up[counter_for_char]) define_for_changes(A2[ii][jj], ii, jj, 'w'); //'w' - цвет
					}
				}
			}
		}
	}
	void changes_for_black_figures(string array){ // поиск чёрных фигур 
		//функция предназначена для заполнения битыми клетками двумерного массива for_black_figures
		if (array == "A1"){//бегает по главному двумерному массиву и ищет чёрные фигуры
			for (int ii = 0; ii < 8; ii++){ 
				for (int jj = 1; jj < 9; jj++){
					for (int counter_for_char = 0; counter_for_char < down.size() - 1; counter_for_char++){ //(down.size() - 1) т.к. up и down включают в себя 0, находящийся в конце массива
						if (A[ii][jj] == down[counter_for_char]) define_for_changes(A[ii][jj], ii, jj, 'b'); //'b' - цвет
					}
				}
			}						
		}
		if (array == "A2"){//бегает по копии двумерного массива и ищет чёрные фигуры
			for (int ii = 0; ii < 8; ii++){ 
				for (int jj = 1; jj < 9; jj++){
					for (int counter_for_char = 0; counter_for_char < down.size() - 1; counter_for_char++){ //(down.size() - 1) т.к. up и down включают в себя 0, находящийся в конце массива
						if (A2[ii][jj] == down[counter_for_char]) define_for_changes(A2[ii][jj], ii, jj, 'b'); //'b' - цвет
					}
				}
			}				
		}
	}
	void define_for_changes(char ch, int ii, int jj, char colour){ 
		/*принимает символ цвета фигуры и вызывает функцию ходов для неё 
		вызываемые функции заполняют двумерные массивы for_black_figures и for_white_figures битыми клетками*/
		if (colour == 'b'){
			if (ch == 'p') all_pawn_moves(ii, jj, 'b');
			if (ch == 'r') all_rook_moves(ii, jj, 'b');
			if (ch == 'b') all_bishop_moves(ii, jj, 'b');
			if (ch == 'h') all_horse_moves(ii, jj, 'b');
			if (ch == 'k') all_king_moves(ii, jj, 'b');
			if (ch == 'q') all_queen_moves(ii, jj, 'b');	
		}
		if (colour == 'w'){
			if (ch == 'P') all_pawn_moves(ii, jj, 'w');
			if (ch == 'R') all_rook_moves(ii, jj, 'w');
			if (ch == 'B') all_bishop_moves(ii, jj, 'w');
			if (ch == 'H') all_horse_moves(ii, jj, 'w');
			if (ch == 'K') all_king_moves(ii, jj, 'w');
			if (ch == 'Q') all_queen_moves(ii, jj, 'w');			
		}
	}

	//функции, которые отмечают битые клетки; начальные координаты самих фигур не учитываются
	void all_rook_moves(int ii, int jj, char colour){ 
		if (colour == 'b'){
			for (int ind_i = ii + 1; ind_i < 8; ind_i++){
				if (A[ind_i][jj] == '0') for_black_figures[ind_i][jj] = '1';
				else{
					for_black_figures[ind_i][jj] = '1';
					break;
				} 			
			}
			for (int ind_i = ii - 1; ind_i >=  0; ind_i--){
				if (A[ind_i][jj] == '0') for_black_figures[ind_i][jj] = '1';
				else{
					for_black_figures[ind_i][jj] = '1';
					break;
				} 			
			}
			for(int ind_j = jj + 1; ind_j < 9; ind_j++){
				if (A[ii][ind_j] == '0') for_black_figures[ii][ind_j] = '1';
				else{
					for_black_figures[ii][ind_j] = '1';
					break;
				} 				
			}
			for (int ind_j = jj - 1; ind_j >  0; ind_j--){
				if (A[ii][ind_j] == '0') for_black_figures[ii][ind_j] = '1';
				else{
					for_black_figures[ii][ind_j] = '1';
					break;
				} 			
			}				
		

		}
		if (colour == 'w'){
			for (int ind_i = ii + 1; ind_i < 8; ind_i++){
				if (A[ind_i][jj] == '0') for_white_figures[ind_i][jj] = '1';
				else{
					for_white_figures[ind_i][jj] = '1';
					break;
				} 			
			}
			for (int ind_i = ii - 1; ind_i >=  0; ind_i--){
				if (A[ind_i][jj] == '0') for_white_figures[ind_i][jj] = '1';
				else{
					for_white_figures[ind_i][jj] = '1';
					break;
				} 			
			}
			for(int ind_j = jj + 1; ind_j < 9; ind_j++){
				if (A[ii][ind_j] == '0') for_white_figures[ii][ind_j] = '1';
				else{
					for_white_figures[ii][ind_j] = '1';
					break;
				} 				
			}
			for (int ind_j = jj - 1; ind_j >  0; ind_j--){
				if (A[ii][ind_j] == '0') for_white_figures[ii][ind_j] = '1';
				else{
					for_white_figures[ii][ind_j] = '1';
					break;
				} 			
			}			
		}
	}
	void all_bishop_moves(int ii, int jj, char colour){
		if(colour == 'b'){
			for (int ind_i = ii + 1,  ind_j = jj + 1; ind_i < 8, ind_j < 9; ind_i++, ind_j++){
				if (A[ind_i][ind_j] == '0') for_black_figures[ind_i][ind_j] = '1';
				else{
					for_black_figures[ind_i][ind_j] = '1';
					break;
				} 								
			}
			for (int ind_i = ii + 1,  ind_j = jj - 1; ind_i < 8, ind_j > 0; ind_i++, ind_j--){
				if (A[ind_i][ind_j] == '0') for_black_figures[ind_i][ind_j] = '1';
				else{
					for_black_figures[ind_i][ind_j] = '1';
					break;
				} 								
				
			}	
			for (int ind_i = ii - 1,  ind_j = jj - 1; ind_i >= 0, ind_j > 0; ind_i--, ind_j--){
				if (A[ind_i][ind_j] == '0') for_black_figures[ind_i][ind_j] = '1';
				else{
					for_black_figures[ind_i][ind_j] = '1';
					break;
				} 								
				
			}
			for (int ind_i = ii - 1, ind_j = jj + 1; ind_i >= 0, ind_j < 9; ind_i--, ind_j++){
				if (A[ind_i][ind_j] == '0') for_black_figures[ind_i][ind_j] = '1';
				else{
					for_black_figures[ind_i][ind_j] = '1';
					break;
				} 								
				
			}		
		}
		if (colour == 'w'){
			for (int ind_i = ii + 1, ind_j = jj + 1; ind_i < 8, ind_j < 9; ind_i++, ind_j++){
				if (A[ind_i][ind_j] == '0') for_white_figures[ind_i][ind_j] = '1';
				else{
					for_white_figures[ind_i][ind_j] = '1';
					break;
				} 								
			}
			for (int ind_i = ii + 1, ind_j = jj - 1; ind_i < 8, ind_j > 0; ind_i++, ind_j--){
					if (A[ind_i][ind_j] == '0') for_white_figures[ind_i][ind_j] = '1';
					else{
						for_white_figures[ind_i][ind_j] = '1';
						break;
				} 								
			}	
			for (int ind_i = ii - 1, ind_j = jj - 1; ind_i >= 0, ind_j > 0; ind_i--, ind_j--){
				if (A[ind_i][ind_j] == '0') for_white_figures[ind_i][ind_j] = '1';
				else{
					for_white_figures[ind_i][ind_j] = '1';
					break;
				} 								
			}
			for (int ind_i = ii - 1, ind_j = jj + 1; ind_i >= 0, ind_j < 9; ind_i--, ind_j++){
					if (A[ind_i][ind_j] == '0') for_white_figures[ind_i][ind_j] = '1';
					else{
						for_white_figures[ind_i][ind_j] = '1';
						break;
					} 								
			}		
		}
	}
	void all_queen_moves(int ii, int jj, char colour){
		all_bishop_moves(ii, jj, colour);
		all_rook_moves(ii, jj, colour);
	}
	void all_king_moves(int ii, int jj, char colour){
		if (colour == 'b'){
			if (ii + 1 < 8){
				for_black_figures[ii+1][jj] = '1';
				if (jj + 1 < 9)	for_black_figures[ii+1][jj+1] = '1';				
				if (jj - 1 > 0)	for_black_figures[ii+1][jj-1] = '1';
				
			}
			if (ii - 1 >= 0){
				for_black_figures[ii-1][jj] = '1';	
				if (jj + 1 < 9) for_black_figures[ii-1][jj-1] = '1';
				if (jj - 1 > 0)	for_black_figures[ii-1][jj+1] = '1';
			}
			if (jj - 1 > 0)	for_black_figures[ii][jj-1] = '1';
			if (jj + 1 < 9) for_black_figures[ii][jj+1] = '1';

		}
		if (colour == 'w'){
			if (ii + 1 < 8){
				for_white_figures[ii+1][jj] = '1';
				if (jj + 1 < 9)	for_white_figures[ii+1][jj+1] = '1';				
				if (jj - 1 > 0)	for_white_figures[ii+1][jj-1] = '1';
				
			}
			if (ii - 1 >= 0){
				for_white_figures[ii-1][jj] = '1';	
				if (jj + 1 < 9) for_white_figures[ii-1][jj-1] = '1';
				if (jj - 1 > 0)	for_white_figures[ii-1][jj+1] = '1';
			}
			if (jj - 1 > 0)	for_white_figures[ii][jj-1] = '1';
			if (jj + 1 < 9) for_white_figures[ii][jj+1] = '1';

		}
	}
	void all_horse_moves(int ii, int jj, char colour){
		if (colour == 'b'){
			if (ii + 1 < 8){
				if (jj + 2 < 9) for_black_figures[ii+1][jj+2] = '1';
				if (jj - 2 > 0) for_black_figures[ii+1][jj-2] = '1';			
			}
			if (ii - 1 >= 0){
				if (jj + 2 < 9) for_black_figures[ii-1][jj+2] = '1';
				if (jj - 2 > 0) for_black_figures[ii-1][jj-2] = '1';				
			}
			if (ii + 2 < 8){
				if (jj + 1 < 9) for_black_figures[ii+2][jj+1] = '1';
				if (jj - 1 > 0) for_black_figures[ii+2][jj-1] = '1';				
			}
			if (ii - 2 >= 0){
				if (jj + 1 < 9) for_black_figures[ii-2][jj+1] = '1';
				if (jj - 1 > 0) for_black_figures[ii-2][jj-1] = '1';				
			}
		}
		if (colour == 'w'){
			if (ii + 1 < 8){
				if (jj + 2 < 9) for_white_figures[ii+1][jj+2] = '1';
				if (jj - 2 > 0) for_white_figures[ii+1][jj-2] = '1';			
			}
			if (ii - 1 >= 0){
				if (jj + 2 < 9) for_white_figures[ii-1][jj+2] = '1';
				if (jj - 2 > 0) for_white_figures[ii-1][jj-2] = '1';				
			}
			if (ii + 2 < 8){
				if (jj + 1 < 9) for_white_figures[ii+2][jj+1] = '1';
				if (jj - 1 > 0) for_white_figures[ii+2][jj-1] = '1';				
			}
			if (ii - 2 >= 0){
				if (jj + 1 < 9) for_white_figures[ii-2][jj+1] = '1';
				if (jj - 1 > 0) for_white_figures[ii-2][jj-1] = '1';				
			}
		}
	}
	void all_pawn_moves(int ii, int jj, char colour){
		if (colour == 'b'){
			if (ii + 1 < 8){
				if (jj - 1 > 0) for_black_figures[ii+1][jj-1] = '1';
				if (jj + 1 < 9) for_black_figures[ii+1][jj+1] = '1';
			}
		}
		if (colour == 'w'){
			if (ii - 1 >= 0){
				if (jj - 1 > 0) for_white_figures[ii-1][jj-1] = '1';
				if (jj + 1 < 9) for_white_figures[ii-1][jj+1] = '1';				
			}
		}
	}

	void remove_array(){ //удаление данных с массивов битых клеток
		for (int h  = 0; h < 8; h++){
			for (int k = 1 ; k < 9; k++){
				for_black_figures[h][k] = '0';
				for_white_figures[h][k] = '0';
			}
		}

	}
	bool check_for_kings(string array){ // проверка на шах
		if (array == "A1"){// проверка на шах в главном двумерном массиве
			if (!(determine  % 2)){//проверка для чёрного короля
				for (int h = 0; h < 8; h++){
					for (int k = 1; k < 9; k++){
						if(A[h][k] == 'k'){
							if (for_white_figures[h][k] == '1'){
								return true;
							}
							else return false; 
							break;
						}
					}
				}
				return false;
			}
			if (determine % 2){//проверка для белого короля
				for (int h = 0; h < 8; h++){
					for (int k = 1; k < 9; k++){
						if(A[h][k] == 'K'){
							if (for_black_figures[h][k] == '1'){
								return true;
							}
							else return false;
							break;
						}
					}			
				}
				return false;
			}
		}
		if (array == "A2"){ //проверка на шах в копии двумерного массива.
							// нужно для проверки на то, увёл введёный ход фигуры короля от шаха или нет
			if (!(determine  % 2)){ //проверка для чёрного короля
				for (int h = 0; h < 8; h++){
					for (int k = 1; k < 9; k++){
						if(A2[h][k] == 'k'){
							if (for_white_figures[h][k] == '1'){
								return true;
							}
							else return false;
							break;
						}
					}
				}
				return false;
			}
			if (determine % 2){//проверка для белого короля
				for (int h = 0; h < 8; h++){
					for (int k = 1; k < 9; k++){
						if(A2[h][k] == 'K'){
							if (for_black_figures[h][k] == '1'){
								return true;
							}
							else return false;
							break;
						}
					}			
				}
				return false;
			}
		}		
		return false;
	}
	void copy_array(){ //копирует главный двумерный массив
		for (int h = 0; h < 9; h++){
			for (int k = 0; k < 9; k++){
				A2[h][k] = A[h][k];
			}
		}
	}

	bool search_for_checkmate(){//проверка на мат
		 	/*	h, k и ind_h, ind_k являются координатами клеток. 
				h и k - текущее местоположение фигуры, 
				ind_h и ind_k - то, куда её нужно переставить.
				ind_h и ind_k перебрираются циклом с последующим вызовом функций для проверки на возможность хода
				Если ход возможен,то скопировать главный массив в A2(при первой перестановки будет незаметно,
				но т.к перестановка, которая не помогла королю,не стирается, все ходы фигур будут оставаться)
				после происходит перестановка фигуры в массиве A2.
				Затем обновляются данные о битых ходах(предварительно нужно стереть предыдущие значения);
				после этого происходит проверка на шах.
				если шаха нет, то вся функция прекращает работу, возвращая false,
				иначе значения для той фигуры перебираются снова.
				после обработки одной фигуры цикл ищет следующую до тех пор, пока шах не исчезнет
				или до тех пор, пока не обработаются все фигуры*/	

			/*	flag_for_move преднадзначен для проверки на возможность хода;
				flag_for_check нужен для проверки на шах*/				
		copy_array();
		if (!(determine%2)){ //для чёрных фигур
			bool flag_for_move, flag_for_check = 1; 
			for (int h = 0; h < 8; h++){
				for (int k = 1; k < 9; k++){
					for (int counter_for_char = 0; counter_for_char < down.size() - 1; counter_for_char++){ 
						if (A2[h][k] == down[counter_for_char]){//если фигура найдена
							switch (A2[h][k]){//определяется тип фигуры
								case 'p':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = pawn_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check){
												return false; //если перестановка помогла, то это не мат
											}
										}
									}
									break;
								}
								case 'r':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = rook_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
								case 'b':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = bishop_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
								case 'h':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = horse_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
								case 'q':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = queen_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
								case 'k':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = pawn_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
							}
						} 
				}
			}
			}
			return true;
		}
		if (determine%2){//для белых фигур
			bool flag_for_move, flag_for_check = 1; 
			for (int h = 0; h < 8; h++){
				for (int k = 1; k < 9; k++){
					for (int counter_for_char = 0; counter_for_char < up.size() - 1; counter_for_char++){ 
						if (A2[h][k] == up[counter_for_char]){//если фигура найдена
							switch (A2[h][k]){//определяется тип фигуры
								case 'P':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = pawn_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}
									break;
								}
								case 'R':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = rook_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
								case 'B':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = bishop_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
								case 'H':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = horse_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
								case 'Q':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = queen_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
								case 'K':{
									for (int ind_h = 0; ind_h < 8; ind_h++){	//цикл перебирает все корординаты массива,
										for (int ind_k = 1; ind_k < 9; ind_k++){//которые потом указыываются в вызове функции перестановки
											flag_for_move = pawn_move(h, k, ind_h, ind_k);
											if (flag_for_move){
												copy_array(); //копирование
												rearranging(h, k, ind_h, ind_k, "A2");//перестановка
												remove_array();//удаление данных о битых клетках
												changes_for_black_figures("A2");// заполнение массивов 
												changes_for_white_figures("A2");// битыми клетками
												flag_for_check = check_for_kings("A2");//проверка на шах(возвращает 0, если шаха нет)
											}
											if (!flag_for_check) return false; //если перестановка помогла, то это не мат
										}
									}									
									break;
								}
							}
						} 
					}
				}
			}
			return true;
		}
		return true;
	}
};



int main(){
	print(); // вывод матрицы на консоль
	/*determine = 0 - счётчик для определения противника
		белые фигуры(верхний регистр) - нечётные; 
		чёрные фигуры(нижний регистр) - чётные*/
	char ch, a, new_ch, new_a; // номера клетки, введёные с консоли
	/*  ch и a - координаты (буква и цифра) текущего местоположения фигуры
		new_ch и new_a - координаты (буква и цифра) клетки, на которую нужно переставить фигуру*/
    int i, j, new_i, new_j;	//обработаннные индексы матрицы (числа). 
	/*	i - строка (cooтветствует цифрам); 
		j - столбец (соответствует буквам);
		new_i и new_j - обработанные координаты клетки, на которую нужно переставить фигуру*/
	bool flag = 1,  flag_for_kings; //flag_for_kings предназначен для определения шаха и последующих действия связанных с этим
	chess_figures step;

	while(true){
		determine++;
		flag_for_kings = step.check_for_kings("A1");	//проверка на шах в главном массиве	
		if (flag_for_kings) {
			if (step.search_for_checkmate()){
				cout << "  checkmate" << endl;
				break;
			}
		}
		if (flag_for_kings) cout << " The king is attacked. Help him " << endl;
		
		if ((determine % 2)) cout << " white's move: ";
		else cout << " black's move: ";
		do{ // текущее местонахождение фигуры
			flag = 1;
			cin >> ch >> a;
			j = switch_char(ch, flag);
			if (flag) i = switch_int(a, flag);
			if (flag) {
				if (A[i][j] == '0'){
					cout << " error: empty cell.\n Re-entry: ";
					flag = 0;
				}
			}
		} while (!flag);
	
    	do{ // место, куда нужно переставить фигуру
			flag = 1;
			cin >> new_ch >> new_a;
			new_j = switch_char(new_ch, flag);
			if (flag) new_i = switch_int(new_a, flag);
		} while (!flag);
		
		if(flag_for_kings && step.define_figure(i, j, new_i, new_j)){ // если шах и ход правильный в плане возможности перестановки
			step.copy_array();
			rearranging(i, j, new_i, new_j, "A2");
			step.remove_array(); 
			step.changes_for_black_figures("A2");
			step.changes_for_white_figures("A2");	
			flag_for_kings = step.check_for_kings("A2");	
		}
		if ((!flag_for_kings) && step.define_figure(i, j, new_i, new_j)){
	    	rearranging (i, j, new_i, new_j, "A1"); // перемещение фигуры
		} 
		else {
			cout << " wrong move" << endl;
			determine--;
			continue;
		}
		system("cls");
		print();
		step.remove_array();
		step.changes_for_black_figures("A1");//в двух матрицах отмечаются битые клетки для чёрных и белых фигур
		step.changes_for_white_figures("A1"); 
	}

    system("pause");
}