#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

using namespace std;
    char A[9][9]{
    {'8','r','b','k','e','q','k','b','r'},
    {'7','p','p','p','p','p','p','p','p'},
    {'6','0','0','0','0','0','0','0','0'},
    {'5','0','0','0','0','0','0','0','0'},
    {'4','0','0','0','0','0','0','0','0'},
    {'3','0','0','0','0','0','0','0','0'},
    {'2','P','P','P','P','P','P','P','P'},
    {'1','R','B','K','E','Q','K','B','R'},
    {' ', 'A','B','C','D','E','F','G','H'}
	};
	void print(){
		for (int i = 0; i < 9; i++) {
        	for (int j = 0; j < 9; j++) cout << setw(2) << A[i][j];
        cout << endl;
    	}	
	}
	void input(){
		int b; char a;
		cin >> a >> b;
	}
	int switch_char (char ch, bool &flag){ //j (столбец)
        int j;
		switch (ch){
			case 'A':{
				j = 1;
				break;
			}
			case 'B':{
				j = 2;
				break;
			}
			case 'C':{
				j = 3;
				break;
			}
			case 'D':{
				j = 4;
				break;
			}
			case 'E':{
				j = 5;
				break;
			}
			case 'F':{
				j = 6;
				break;
			}
			case 'G':{
				j = 7;
				break;
			}
			case 'H':{
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
	int switch_int (int b, bool &flag){//i (строка)
        int i;
		switch (b){
			case 1:{
				i = 7;
				break;
			}
			case 2:{
				i = 6;
				break;
			}
			case 3:{
				i = 5;
				break;
			}
			case 4:{
				i = 4;
				break;
			}
			case 5:{
				i = 3;
				break;
			}
			case 6:{
				i = 2;
				break;
			}
			case 7:{
				i = 1;
				break;
			}
			case 8:{
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

int main(){
	print(); // вывод матрицы на консоль
	//int i, j;  индексы матрицы. i - строка(cooтветствует цифрам); j - столбец(соотв. буквам)
	char ch, new_ch; int a, new_a, separator; // номер клетки
    int i, j, new_i, new_j;
	bool flag = 1; 

	do{ // текущее местонахождение фигуры
		flag = 1;
		cin >> ch >> a;
		j = switch_char(ch, flag);
		if (flag) i = switch_int(a, flag);
	} while (!flag);
	//cout << i << " " << j << endl;
    //cin >> separator;
    do{ // место, куда нужно переставить фигуру
		flag = 1;
		cin >> new_ch >> new_a;
		new_j = switch_char(new_ch, flag);
		if (flag) new_i = switch_int(new_a, flag);
	} while (!flag);
	//cout << new_i << " " << new_j << endl;
    swap(A[i][j], A[new_i][new_j]);
    print();
    system("pause");
	
}