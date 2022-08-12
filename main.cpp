#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
	int i, j;
	void print(char ( &A )[9][9] ){
		for (int i = 0; i < 9; i++) {
        	for (int j = 0; j < 9; j++) cout << setw(2) << A[i][j];
        cout << endl;
    	}	
	}
	void input(){
		int b; char a;
		cin >> a >> b;
	}
	void switch_char (char a, bool &flag){ //j
		switch (a){
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
	}
	void switch_int (int b, bool &flag){//i
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
	}

int main(){
	char A[9][9]{
    {'8','0','0','0','0','0','0','0','0'},
    {'7','0','0','0','0','0','0','0','0'},
    {'6','0','0','0','0','0','0','0','0'},
    {'5','0','0','0','0','0','0','0','0'},
    {'4','0','0','0','0','0','0','0','0'},
    {'3','0','0','0','0','0','0','0','0'},
    {'2','0','0','0','0','0','0','0','0'},
    {'1','0','0','0','0','0','0','0','0'},
    {' ', 'A','B','C','D','E','F','G','H'}
	};
	print(A); // вывод матрицы на консоль
	//int i, j;  индексы матрицы. i - строка(cooтветствует цифрам); j - столбец(соотв. буквам)
	char a; int b; // номер клетки
	bool flag = 1; 

	do{
		flag = 1;
		cin >> a >> b;
		switch_char(a, flag);
		if (flag) switch_int(b, flag);
	} while (!flag);
	cout << i << " " << j;


	
}