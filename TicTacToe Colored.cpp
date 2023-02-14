#include <iostream>
#include <conio.h>
#include <cwchar>
#include <windows.h>

using namespace std;

void setConsoleSize(int f_size){
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = f_size;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Calibri");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),FALSE,&cfi);
}

void printInputMatrix();
void printBoard();
int addMark();
int check();

int pColors[9] = {247,247,247,247,247,247,247,247,247};
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

char board[3][3] = {'1','2','3',
					'4','5','6',
					'7','8','9'};
int turn = 1;   //1 - P1 | 0 - P2
char mark = 'O';//O - P1 | X - P2
int input;

int main(){
	setConsoleSize(30);
	SetConsoleTextAttribute(console, BACKGROUND_BLUE|BACKGROUND_GREEN|
									 BACKGROUND_RED|BACKGROUND_INTENSITY);
	int won = 0;
	int validInput = 0;
	
	for( int i=0; i<9; i++ ){
		system("cls");
		printBoard();
		
		if( turn ){
			SetConsoleTextAttribute(console,242);
			cout<<"O - Player 1:"<<endl;	
		} 
		else{
			SetConsoleTextAttribute(console,242);
			cout<<"X - Player 2:"<<endl;	
		} 
		//printInputMatrix();
		//cout<<"Enter Input from Input Matrix: ";
		cin>>input;
		while(input<0 || input >9){
			cout<<"Invalid Input please Re-Enter Input:";
			cin>>input;
		}
		
		if( turn ) pColors[input-1] = 242;
		else pColors[input-1] = 252;
		
		if( turn ) mark = 'O';
		else mark = 'X';
		
		validInput = addMark();
		if( !validInput ){
			i--;
			continue;
		}
		won = check();
		if( won ){
			system("cls");
			printBoard();
			if( turn )
			{
				SetConsoleTextAttribute(console,242);
				cout<<endl<<"**************************";
				cout<<endl<<"*** Player 1 - You Won ***";
				cout<<endl<<"**************************";
			}
			else{
				SetConsoleTextAttribute(console,252);
				cout<<endl<<"**************************";
				cout<<endl<<"*** Player 2 - You Won ***";
				cout<<endl<<"**************************";
			}
			getch();
			break;
		}
		
		if( i==8 ){
			system("cls");
			printBoard();
			cout<<endl<<"*** MATCH DRAW ***";
		}
		turn = !turn;
	}
	return 0;
}

void printInputMatrix(){
	cout<<endl<<endl<<"INPUT MATRIX"<<endl;
	cout<<" 1 | 2 | 3 "<<endl;
	cout<<"-----------"<<endl;
	cout<<" 4 | 5 | 6 "<<endl;
	cout<<"-----------"<<endl;
	cout<<" 7 | 8 | 9 "<<endl;
}
void printBoard(){
	for(int i=0,k=1; i<3; i++){
		for(int j=0; j<3; j++,k++){
			SetConsoleTextAttribute(console, pColors[k-1]);
			cout<<" "<<board[i][j];
			SetConsoleTextAttribute(console, 247);
			if(j<2) cout<<" |";
		}
		cout<<endl;
		if(i<2) cout<<"-----------------"<<endl;
	}
}
int addMark(){
	for(int i=0,k=1; i<3; i++){
		for(int j=0; j<3; j++,k++){
			if( k==input ){
				if( board[i][j]!='X' && board[i][j]!='O' ){
					board[i][j] = mark;
					return 1;
				}
				else{
					cout<<"Invalid Input";
					getch();
					return 0;
				}
			}	
		}
	}
}

int check(){
	// checking rows
	if( board[0][0]==mark && board[0][1]==mark && board[0][2]==mark )
		return 1;
	if( board[1][0]==mark && board[1][1]==mark && board[1][2]==mark )
		return 1;
	if( board[2][0]==mark && board[2][1]==mark && board[2][2]==mark )
		return 1;
		
	
	// checking cols
	if( board[0][0]==mark && board[1][0]==mark && board[2][0]==mark )
		return 1;
	if( board[0][1]==mark && board[1][1]==mark && board[2][1]==mark )
		return 1;
	if( board[0][2]==mark && board[1][2]==mark && board[2][2]==mark )
		return 1;
	
	// checking diagonals
	if( board[0][0]==mark && board[1][1]==mark && board[2][2]==mark )
		return 1;
	if( board[0][2]==mark && board[1][1]==mark && board[2][0]==mark )
		return 1;
		
	return 0;
}
