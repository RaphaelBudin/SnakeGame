#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

const unsigned int MAXC = 60;
const unsigned int MAXL = 20;

enum Movimento {A = 8,S = 2 , D = 6, W = 8};
typedef enum Movimento movimento;


struct Cabeca_cobra {
	int posx;
	int poxy;
	movimento mov;
};


//Falta - 1) Desenhar cobra; 2) Desenhar fruta
void desenharTela(void){
	
	//************************************
	//	TABULEIRO
	//************************************

	//Desenhar primeira linha inteira
		_gotoxy(0, 0);
		for (int i = 0; i < MAXC; ++i)
			printf("%c", '*');
	//Desenhar primeira coluna inteira
		_gotoxy(0,0);
		for (int i = 0; i < MAXL; ++i)
			printf("%c\n", '*');
	//Desenhar última linha inteira
		_gotoxy(MAXL-1, 0);
		for (int i = 0; i < MAXC; ++i)
			printf("%c", '*');
	//Desenhar última coluna inteira
		//_gotoxy(MAXC,0);
		for (int i = 0; i <= MAXL; ++i){
			_gotoxy(MAXC+1, i);
			printf("%c", '*');
		}

	//************************************
	//	COBRA
	//************************************

	//************************************
	//	FRUTO
	//************************************
	
}





int main(void){
	desenharTela();
	while (1){
		_clrscr();
		desenharTela();
		_sleep(1);
	}
	puts("\n\n");
	return 0;
}
