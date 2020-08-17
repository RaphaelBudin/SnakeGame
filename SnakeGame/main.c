#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <string.h>

const unsigned int MAXC = 60;
const unsigned int MAXL = 20;
const int SIMB_COBRA = 190;
const int SIMB_FRUTO = 184;

enum Movimento {A = 8,S = 2 , D = 6, W = 8, Z = 0};
typedef enum Movimento movimento;

typedef struct corpo{
	int posx;
	int posy;
	struct corpo *pt;
	movimento mov;
}Corpo;

typedef struct cabeca{
	int posx;
	int posy;
	Corpo *p;		//Por algum motivo, o typedef não funcionou para o ponteiro
	movimento mov;
	int xPrev;
	int yPrev;
	unsigned int frutasComidas;
}Cabeca_cobra;

typedef struct fruto {
	int posx;
	int posy;
}Fruto;

void gameOver(void){
	printf("\n\n\n\n\nVoce perdeu!\n\n\n");
}

void adicionarCorpo_Cabeca(Cabeca_cobra *cabeca){
	Corpo corpo = {cabeca->xPrev, cabeca->yPrev, NULL, cabeca->mov};
	cabeca->p = &corpo;
}

void adicionarCorpo_Corpo(Cabeca_cobra *cabeca, Corpo *corpo){
	int x = 0, y = 0;
	switch(cabeca->mov){
		case 8:			x = 1 + cabeca->posx;			break;
		case 2:			x = 1 - cabeca->posx;			break;
		case 6:			y = 1 + cabeca->posx;			break;
		case 4:			y = 1 - cabeca->posy;			break;
		case 0:			break;	
	}
	Corpo novoCorpo = {x,y,cabeca->p, corpo->mov};
	cabeca->p = &novoCorpo;
}

void desenharCoordenada(int x, int y, char simbolo){
	_gotoxy(x,y);
	printf("%c", simbolo);
}

void desenharTela(void){
	//Desenhar primeira linha inteira
		_gotoxy(0, 0);
		for (unsigned int i = 0; i < MAXC/2-1; ++i)
			printf("%c ", '*');

	//Desenhar primeira coluna inteira
		_gotoxy(0,0);
		for (unsigned int i = 0; i < MAXL; ++i)
			printf("%c\n", '*');

	//Desenhar última linha inteira
		_gotoxy(MAXL-1, 0);
		for (unsigned int i = 0; i < MAXC/2; ++i)
			printf("%c ", '*');

	//Desenhar última coluna inteira
		for (unsigned int i = 0; i <= MAXL; ++i){
			_gotoxy(MAXC+1, i);		
			printf("%c", '*');
		}
}

void apagarCoordenada (int x, int y){
	_gotoxy(x,y);
	printf("%c", ' ');
}	

//Função pouco legível
void desenharCobra (Cabeca_cobra cobrinha){
	apagarCoordenada(cobrinha.xPrev, cobrinha.yPrev);
	_gotoxy(cobrinha.posx, cobrinha.posy);
	printf("%c", (char)SIMB_COBRA);		//Cabeca
	
	//		IMPLEMENTAR LÓGICA DE LINKED LISTS	
	

	//Retoma ao normal
	_gotoxy(cobrinha.posx, cobrinha.posy);
	printf("%c", (char)SIMB_COBRA);	
}

Fruto gerarFrutoInicial(void){
	Fruto temp = {0,0};
	do{
		temp.posx = rand()%MAXC;
		temp.posy = rand()%MAXL;
	}while (temp.posx <= 1 || temp.posy <= 1 || temp.posx >= MAXC-1 || temp.posy >= MAXL-1 || (temp.posx == MAXC/2-1 && temp.posx == MAXL/2-1));
	//A linha acima verifica se a Fruta Inicial não é gerada na mesma posição que a cobrinha começa
	//Da mesma forma verifica se não é iniciada nas bordas
	return temp;
}

void gerarFruto(Fruto *fruta, int xCobrinha, int yCobrinha){
	apagarCoordenada(fruta->posx, fruta->posy);
	do{
		fruta->posx = rand()%MAXC;
		fruta->posy = rand()%MAXL;
	}while 		((fruta->posx == xCobrinha && fruta->posy == yCobrinha) 		|| 	/* Não gerar fruto em cima da cobrinha*/
				(fruta->posx <= 1 || fruta ->posx == MAXC-1 						||	/* Não gerar fruto nas extremidades do eixo X*/
 				fruta->posy <= 1 || fruta ->posx == MAXL-1));							/* Não gerar fruto nas extremidades do eixo Y*/

	_gotoxy(fruta->posx, fruta->posy);
	printf("%c", SIMB_FRUTO);
}

void baterParede(Cabeca_cobra *cobrinha, _Bool *gameOver){
	//Os comentários abaixo são válidos enquanto a correção da renderização das bordas não for aplicada (ou seja, a coluna adicional não for removida)

	//A primeira coluna é renderizada em X = 1
	if (cobrinha->posx <= 1 || cobrinha->posx >= MAXC)		 *gameOver =  1;
	//A primeira linha é renderizada em Y = 1 e a última linha é renderizada em Y = 21 
	if (cobrinha->posy <=1 || cobrinha->posy > MAXL)  		 *gameOver =  1;
}

void lerMovimentoCobra (Cabeca_cobra *cobrinha, _Bool *gameOver){
	switch(toupper(_getch())){
		case 'A':			cobrinha->mov = 4;				break;
		case 'D':			cobrinha->mov = 6;				break;
		case 'S':			cobrinha->mov = 2;				break;
		case 'W':			cobrinha->mov = 8;				break;
		case 'X':			*gameOver = 1;					break;
		default: 												break;
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
		case 0: 						break;
	}
}

void comerFruto (Cabeca_cobra *cobrinha, Fruto *frutinha){
	//Quando as frutinhas são geradas em colunas pares, a cobrinha (que se movimenta de 2 em 2 no eixo X) não conseguia comer a fruta
	//Logo é preciso verificar se a posição atual da cobrinha menos um contém a fruta (indicando que ela passou por cima)
	if (
		(
			(cobrinha->posx == frutinha->posx) || (cobrinha->posx == frutinha->posx+1)
		) 
			&& cobrinha->posy == frutinha->posy
	   )
	{
		cobrinha->frutasComidas++;
		gerarFruto(frutinha, cobrinha->posx, cobrinha->posy);
 		if (cobrinha->p != NULL) adicionarCorpo_Cabeca(cobrinha);
		else adicionarCorpo_Corpo(cobrinha, cobrinha->p);
	}
}

int desenharInfoCorpo(Cabeca_cobra *cobrinha, Corpo *corpo){
	static unsigned int i =1;
	if (cobrinha->p == NULL)	return 0;	//Só há a cabeça
	/*while (corpo->pt != NULL){
		desenharInfoCorpo(cobrinha, corpo->pt);
	}*/
	return 1;
}

void desenharInformacoes(Cabeca_cobra *cobrinha, Fruto *fruta){
	_gotoxy(MAXC,MAXL+5);
	printf("\nPosicao fruta:		X = %i		Y = %i\n", fruta->posx, fruta->posy);
	printf("Posicao Cabeca: 	X = %i		Y = %i\n", cobrinha->posx,  cobrinha->posy);
	printf("Frutinhas Comidas:  %i\n", cobrinha->frutasComidas);
	//desenharInfoCorpo(cobrinha, cobrinha->p);
}

int main(void){
	srand(time(NULL));
	Cabeca_cobra cobrinha = {MAXC/2-1, MAXL/2-1,NULL,6 ,0,0,0};	
	Fruto fruta = gerarFrutoInicial();
	desenharTela();
	desenharCoordenada(fruta.posx, fruta.posy, SIMB_FRUTO);
	
	_Bool game_over = 0;
	while (!game_over){
		desenharInformacoes(&cobrinha, &fruta);
		desenharCobra(cobrinha);
		lerMovimentoCobra(&cobrinha, &game_over);
		movimentarCobra(&cobrinha);
		baterParede(&cobrinha, &game_over);
		comerFruto(&cobrinha, &fruta);
		Sleep(50);
	}
	puts("\n\nFim de Jogo!\n\n\n");
	return 0;
}
