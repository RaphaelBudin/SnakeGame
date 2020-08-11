#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

const unsigned int MAXC = 60;
const unsigned int MAXL = 20;

enum Movimento {A = 8,S = 2 , D = 6, W = 8, Z = 0};
typedef enum Movimento movimento;


typedef struct cabeca{
	int posx;
	int posy;
	struct cabeca *p;		//Por algum motivo, o typedef não funcionou para o ponteiro
	movimento mov;
}Cabeca_cobra;

void adicionarCorpo(Cabeca_cobra *cabeca){
	Cabeca_cobra corpo = {cabeca->posx, cabeca->posy, NULL, 0 };
	cabeca->p = &corpo;
}

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
}

void desenharCobra (Cabeca_cobra cobrinha){
	_gotoxy(cobrinha.posx, cobrinha.posy);
	printf("%c", (char)259);		//Cabeca
	while (cobrinha.p != NULL){	//Corpo
		cabeca *proximo = &(cobrinha.p);
		int nx = cobrinha->p.posx;
		int ny = cobrinha->p.posy;
		_gotoxy(nx, ny);
		printf("%c", (char)259);
		
	}
	_gotoxy(cobrinha.posx, cobrinha.posy);
	printf("%c", (char)259);	
}

void desenharFruto(){
		
}

void lerMovimentoCobra (Cabeca_cobra *cobrinha){
	switch(toupper(_getch())){
		case 'A':
			cobrinha->mov = 4;
			break;
		case 'D':
			cobrinha->mov = 6;
			break;
		case 'S':
			cobrinha->mov = 2;
			break;
		case 'W':
			cobrinha->mov = 8;
			break;

		default: break;
	}
}

void movimentarCobra (Cabeca_cobra *cobrinha){
	switch(cobrinha->mov){
		case 2: cobrinha->posy++; 	break;
		case 4: cobrinha->posx--; 	break;
		case 6: cobrinha->posx++; 	break;
		case 8: cobrinha->posy--;	break;
	}
}

int main(void){
	Cabeca_cobra cobrinha = {MAXC/2-1, MAXL/2-1,NULL,6 };
	desenharTela(cobrinha);
	while (1){
		_clrscr();

		desenharTela(cobrinha);
		_sleep(1);
	}
	puts("\n\n");
	return 0;
}
