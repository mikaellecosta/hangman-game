#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

#define TAMANHO_PALAVRA 20

char palavrasecreta [TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

int letraexiste(char letra) {

	for(int j = 0; j < strlen(palavrasecreta); j++) {
		if(letra == palavrasecreta[j]) {
			return 1;
		}
	}

	return 0;
}

int chuteserrados() {
	int erros = 0;

	for(int i = 0; i < chutesdados; i++) {
		
		if(!letraexiste(chutes[i])) {
			erros++;
		}
	}

	return erros;
}

int enforcou() {
	return chuteserrados() >= 5;
}

int ganhou() {
	for(int i = 0; i < strlen(palavrasecreta); i++) {
		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}

	return 1;
}


void abertura() {
	printf("/****************/\n");
	printf("/ Jogo de Forca */\n");
	printf("/****************/\n\n");
}

void chuta() {
char chute;
  
// QUESTÃO 1  -

  do{
  printf("Digite uma letra maiúscula: ");
	scanf(" %c", &chute);
    
  } while (chute < 'A' || chute > 'Z');
 

	if(letraexiste(chute)) {
		printf("Você acertou: a palavra tem a letra %c\n\n", chute);
	} else {
		printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
	}

	chutes[chutesdados] = chute;
	chutesdados++;
}

int jachutou(char letra) {
	int achou = 0;
	for(int j = 0; j < chutesdados; j++) {
		if(chutes[j] == letra) {
			achou = 1;
			break;
		}
	}

	return achou;
}

void desenhaforca() {

	int erros = chuteserrados();

	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

	for(int i = 0; i < strlen(palavrasecreta); i++) {

		if(jachutou(palavrasecreta[i])) {
			printf("%c ", palavrasecreta[i]);
		} else {
			printf("_ ");
		}

	}
	printf("\n");

}

void escolhepalavra() {
	FILE* f;

	f = fopen("palavras.txt", "r");
	if(f == 0) {
		printf("Banco de dados de palavras não disponível\n\n");
		exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%d", &qtddepalavras);

	srand(time(0));
	int randomico = rand() % qtddepalavras;

	for(int i = 0; i <= randomico; i++) {
		fscanf(f, "%s", palavrasecreta);
	}

	fclose(f);
}


void adicionapalavra() {
	char quer;

	printf("Você deseja adicionar uma nova palavra no jogo (S/N)?");
	scanf(" %c", &quer);

	if(quer == 'S') {
		char novapalavra[TAMANHO_PALAVRA];
    
  // QUESTAO 2 -  
   do{
      int cont = 1;
  		printf("Digite a nova palavra, em letras maiúsculas: ");
  		scanf(" %s", novapalavra);
      for(int i = 0; i < strlen(novapalavra); i++){
        if(novapalavra[i]<'A' || novapalavra[i]>'Z'){
          cont = 0;
          printf("Invalido! Digite apenas letras maiusculas");
          break;
        }
      }
    }while(0);

    if(verifica_palavra(novapalavra)){
      FILE* f;

  		f = fopen("palavras.txt", "r+");
  		if(f == 0) {
  			printf("Banco de dados de palavras não disponível\n\n");
  			exit(1);
  		}
      
  		int qtd;
  		fscanf(f, "%d", &qtd);
  		qtd++;
  		fseek(f, 0, SEEK_SET);
  		fprintf(f, "%d", qtd);
  
  		fseek(f, 0, SEEK_END);
  		fprintf(f, "\n%s", novapalavra);
  
  		fclose(f);
    }else{
      printf("\nPalavra já existe no arquivo de palavras!!!");
    }
	}
}  

int verifica_palavra(char novapalavra[]){
  
  FILE* f;

  f = fopen("palavras.txt", "r");
  if(f == 0) {
    printf("Banco de dados de palavras não disponível\n\n");
    exit(1);
  }

  int retorno;
  int qtddepalavras;
  char palavra[TAMANHO_PALAVRA];
  
	fscanf(f, "%d", &qtddepalavras);
  for(int i = 0; i <= qtddepalavras; i++) {
    fscanf(f, "%s", palavra);
    retorno = strcmp(novapalavra, palavra);
    if(retorno == 0){break;}
  }
  fclose(f);
  return retorno;
}
//QUESTÃO 4 -
void nivel_dificuldade(){
  int nivel;
  printf("\nQual o nível de dificuldade?\n");
  printf("[1]Fácil [2]Médio [3]Difícil\n\n");
  do{
    printf("Escolha: ");
    scanf("%d",&nivel);
    if(nivel!=1 && nivel!=2 && nivel!=3){
      printf("Opção Inválida!");
    }else{break;}
  }while(1);

int cabeca, corpo, braco, perna;
  
  switch(nivel){
    case 1:
      cabeca = 5;
      corpo = 10;
      braco = 15;
      perna = 20;
      break;
    case 2:
      cabeca = 3;
      corpo = 6;
      braco = 9;
      perna = 12;
      break;
    case 3:
      cabeca = 2;
      corpo = 4;
      braco = 6;
      perna = 8;
      break;
  }
  printf("Você tem %d tentativas! \n",perna);
}

// QUESTAO 6 -
int pontuacao(){
  
  int p, pontos = 1000, perna;
  switch(perna){
	
    case 20:
      p = pontos - 300*chuteserrados();
      break;
    case 12:
      p = pontos - 200*chuteserrados();
      break;
    case 8:
      p = pontos - 100*chuteserrados();
      break;
  }
  return p;
}

void nome(){
  char nome[20];
  printf("Escreva seu nome: ");
  scanf("%s",nome);
  adiciona_rank(nome);
}

void adiciona_rank(char nome[]){
  FILE* f;
  f = fopen("ranking.txt","a");
  if(f == 0) {
    printf("Banco de dados ranking não disponível\n\n");
    exit(1);
  }
  fprintf(f, "\n%d %s", pontuacao(),nome);
  
  fclose(f);
}

int main() {

	abertura();
	escolhepalavra();
  nivel_dificuldade();

	do {

		desenhaforca();
		chuta();

	} while (!ganhou() && !enforcou());
	if(ganhou()) {
		printf("\nParabéns, você ganhou!\n\n");

		printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");
    
  //QUESTÃO 3 -
    adicionapalavra();
	} else {
		printf("\nPuxa, você foi enforcado!\n");
		printf("A palavra era **%s**\n\n", palavrasecreta);

		printf("    _______________         \n");
		printf("   /               \\       \n"); 
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\_______/           \n");
	}

	nome();
}