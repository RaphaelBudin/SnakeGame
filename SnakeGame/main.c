#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

const unsigned int MAXC = 60;
const unsigned int MAXL = 20;
const int SIMB_COBRA = 190;
const int SIMB_FRUTO = 184;

enum Movimento {A = 8,S = 2 , D = 6, W = 8, Z = 0};
typedef enum Movimento movimento;

typedef struct cabeca{
	int posx;
	int posy;
	struct cabeca *p;		//Por algum motivo, o typedef não funcionou para o ponteiro
	movimento mov;
	int xPrev;
	int yPrev;
}Cabeca_cobra;

typedef struct fruto {
	int posx;
	int posy;
}Fruto;

void adicionarCorpo(Cabeca_cobra *cabeca){
	Cabeca_cobra corpo = {cabeca->posx, cabeca->posy, NULL, 0 };
	cabeca->p = &corpo;
}

//Substituir o "for" das linhas e colunas por strings de caracteres
void desenharTela(void){
	//************************************
	//	TABULEIRO
	//************************************

	//Obs: Quando escrevi o código achei bem trivial preencher as linhas e colunas. Código escrito em 10/08/2020.
	//Um dia depois (11/08/2020) vim reler o código que escrevi para desenhar o tabuleiro...
	//Sinceramente, não entendi o porquê dele funcionar.
	//Teoricamente, seria necessário inserir o seguinte comando antes dos printf:
	//		Ex:		_gotoxy(i,0);
	//O comando acima informa que o cursor deve se posicionar na primeira linha do console, mudando apenas a coluna de acordo com "i"
	//Porém parece que o "printf" imprime o texto na posição do cursor, e o que havia antes é empurrado para frente
	//É um efeito não esperado do código
	
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
		for (int i = 0; i <= MAXL; ++i){
			_gotoxy(MAXC+1, i);		//Essa é a única linha lúcida no código, ela explica a lógica perfeitamente
			printf("%c", '*');
		}
}

void apagarCoordenada (int x, int y){
	_gotoxy(x,y);
	printf("%c", ' ');
}

void desenharCobra (Cabeca_cobra cobrinha){
	apagarCoordenada(cobrinha.xPrev, cobrinha.yPrev);
	_gotoxy(cobrinha.posx, cobrinha.posy);
	printf("%c", (char)SIMB_COBRA);		//Cabeca
	while (cobrinha.p != NULL){	//Corpo			--- NÃO TESTADA
		Cabeca_cobra temp = {(cobrinha.p)->posx, (cobrinha.p)->posy,(cobrinha.p)->p,0};
		_gotoxy(temp.posx, temp.posy);
		printf("%c", (char)SIMB_COBRA);
	}
	_gotoxy(cobrinha.posx, cobrinha.posy);
	printf("%c", (char)SIMB_COBRA);	
}

void gerarFruto(Fruto *frutinha){
	int randomX = rand()+2%MAXC-2; 
	int randomY = rand()+2%MAXL-2;
	_gotoxy(randomX, randomY);
	printf("%c", SIMB_FRUTO);

	frutinha->posx = randomX;
	frutinha->posy = randomY;
}

_Bool baterParede(Cabeca_cobra *cobrinha){
	if (cobrinha->posx <= 0 || cobrinha->posx >= MAXC)
		 return 1;
	if (cobrinha->posy <= 0 || cobrinha->posy >= MAXL)
		return 1;
	return 0;
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
	cobrinha->xPrev = cobrinha->posx;
	cobrinha->yPrev = cobrinha->posy;
	switch(cobrinha->mov){
		case 2: cobrinha->posy++; 		break;
		case 4: cobrinha->posx -= 2; 	break;	//As linhas têm o dobro de espaçamento das colunas no console
		case 6: cobrinha->posx += 2; 	break;	//Logo andar duas colunas por vez é a solução para manter a cobrinha uniforme
		case 8: cobrinha->posy--;		break;
	}
}

void gameOver(void){
	printf("\n\n\n\n\nVoce perdeu!\n\n\n");
}

int main(void){
	srand(time(NULL));
	Cabeca_cobra cobrinha = {MAXC/2-1, MAXL/2-1,NULL,6 ,0,0};
	Fruto frutinha = {rand()+2%MAXC-2, rand()+2%MAXL-2};
	desenharTela();
	while (1){
		desenharCobra(cobrinha);
		lerMovimentoCobra(&cobrinha);
		movimentarCobra(&cobrinha);
		if (baterParede(&cobrinha))	{
			gameOver();
			break;					
		}
		Sleep(100);
	}
	puts("\n\n");
	return 0;
}
