#include "Estacionamento.h"
#include "listaencadeada.h"
#include <stdio.h>
#include <stdlib.h>

// Nao existe cor pra vaga VIP ocupada, talvez retirar as cores e deixar apenas
// as padroes.
//  Definições de cores
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_GREEN2 "\x1b[96m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_WHITE "\x1b[0m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_ORANGE "\x1b[33m"

struct Estacionamento{
  int Status_Vaga;
  int Tipo_Vaga;
  int numVaga;
};

typedef struct Estacionamento estacionamento;

// Alocar a matriz do estacionamento
estacionamento **criarEstacionamento(int nlinhas, int ncolunas) {
  estacionamento **E =
      (estacionamento **)malloc(sizeof(estacionamento *) * nlinhas);
  // Verifica se deu erro de memória
  if (E == NULL) {
    printf("Memoria insuficiente.\n");
    exit(1);
  }
  // contador
  int i;
  // For para alocar a quantidade de colunas por linha
  for (i = 0; i < nlinhas; i++) {
    E[i] = (estacionamento *)malloc(sizeof(estacionamento) * ncolunas);
    // Erro no alocamento
    if (E[i] == NULL) {
      printf("Memoria insuficiente.\n");
      exit(1);
    }
  }
  int j;

  // Laço para zerar a posição da matriz
  for (i = 0; i < nlinhas; i++) {
    for (j = 0; j < ncolunas; j++) {
      E[i][j].Status_Vaga = 0;
      E[i][j].Tipo_Vaga = 0;
    }
  }
  estabeleceNumVaga(E, nlinhas, ncolunas);
  return E;
}

void liberaEstacionamento(estacionamento **E, int ncolunas) {
  int i;
  for (i = 0; i < ncolunas; i++) {
    free(E[i]);
  }
  free(E);
}

estacionamento **criarNumVaga(int nlinhas, int ncolunas, estacionamento **E) {
  int k = 0;
  for (int i = 0; i < nlinhas; i++) {
    for (int j = 0; j < ncolunas; j++) {
      // Caso a vaga exsita iguala o numero da vaga a k
      if (E[i][j].Status_Vaga != -1) {
        k++;
        E[i][j].numVaga = k;
      }
    }
  }
  return E;
}

// Antes de ser chamada dever conferir se a vaga existe(E.Status_Vaga != -1)
void mudaCorVaga(int TipoVaga, int StatusVaga) {
  // Vaga Pesssoa com Deficiencia (Livre)
  if (TipoVaga == 1 && StatusVaga == 0) {
    printf(ANSI_COLOR_BLUE);
  }
  // Vaga Pesssoa com Deficiencia (Ocupada)
  else if (TipoVaga == 1 && StatusVaga == 1) {
    printf(ANSI_COLOR_MAGENTA);
  }
  // Vaga Pesssoa Idosa (Livre)
  else if (TipoVaga == 2 && StatusVaga == 0) {
    printf(ANSI_COLOR_YELLOW);
  }
  // Vaga Pesssoa Idosa (Ocupada)
  else if (TipoVaga == 2 && StatusVaga == 1) {
    printf(ANSI_COLOR_ORANGE);
  }
  // Vaga VIP (Livre)
  else if (TipoVaga == 3 && StatusVaga == 0) {
    printf(ANSI_COLOR_GREEN);
  }
  else if (TipoVaga == 3 && StatusVaga == 1) {
    printf(ANSI_COLOR_GREEN2);
  }
  // Vaga Comum (Livre)
  else if (TipoVaga == 0 && StatusVaga == 0) {
    printf(ANSI_COLOR_WHITE);
  }
  // Vaga Comum (Ocupada)
  else if (TipoVaga == 0 && StatusVaga == 1) {
    printf(ANSI_COLOR_RED);
  }
}

void organizaNumero(int *n1, int *n2) {
  int aux;
  if (*n1 > *n2) {
    aux = *n1;
    *n1 = *n2;
    *n2 = aux;
  }
}

int contaCasasNumero(int n) {
  int casas = 1;
  while (n != 0) {
    casas++;
    n = n / 10;
  }
  return casas;
}

void printEstacionamento(estacionamento **E, int nlinhas, int ncolunas) {
  if (E == NULL)
    return;
  int Quantidade_Casas_Elemento_Matriz, Quantidade_Casas;
  // Quantidade_Casas é a quantidade total de casas da matriz
  Quantidade_Casas = contaCasasNumero(nlinhas * ncolunas);
  // Imprime o numero das colunas em cima do estacionamento
  printNumColunas(Quantidade_Casas, ncolunas);
  for (int i = 0; i < nlinhas; i++) {
    for (int j = 0; j < ncolunas; j++) {
      // mudar a cor da vaga conforme condições especificadas
      mudaCorVaga(E[i][j].Tipo_Vaga, E[i][j].Status_Vaga);
      // Print números do estacionamento (Caso a vaga exista)
      if (E[i][j].Status_Vaga != -1 && E[i][j].Status_Vaga != 3) {
        printVagaExistente(Quantidade_Casas, E[i][j].numVaga);
      }
      // Print estacionamento (Caso a vaga NÃO exista)
      else if (E[i][j].Status_Vaga == -1) {
        printVagaInexistente(Quantidade_Casas);
      } else if (E[i][j].Status_Vaga == 3) {
        printVagaManutencao(Quantidade_Casas);
      }
    }
    // Imprime o numero da linha ao lado da matriz do estacionamento
    printf(ANSI_COLOR_WHITE);
    printf(" - %d\n", i);
  }
  estacionamentoLegenda();
}

void printVagaExistente(int Quantidade_Casas, int numVaga) {
  int Quantidade_Casas_Elemento_Matriz;
  Quantidade_Casas_Elemento_Matriz = contaCasasNumero(numVaga);
  printf("|");
  for (int n = 0; n < Quantidade_Casas - Quantidade_Casas_Elemento_Matriz;
       n++) {
    printf("0");
  }
  if(numVaga != 0){
    printf("%d|", numVaga);
  }else{
    printf("|");
  }
}

void printVagaInexistente(int Quantidade_Casas) {
  printf(ANSI_COLOR_WHITE);
  printf(" ");
  for (int n = 0; n < Quantidade_Casas - 1; n++) {
    printf(" ");
  }
  printf(" ");
}

void printVagaManutencao(int Quantidade_Casas) {
  printf(ANSI_COLOR_WHITE);
  printf("|");
  for (int n = 0; n < Quantidade_Casas - 1; n++) {
    if (n % 2 == 0) {
      printf(ANSI_COLOR_YELLOW);
    } else {
      printf(ANSI_COLOR_WHITE);
    }
    printf("/");
  }
  printf(ANSI_COLOR_WHITE);
  printf("|");
}

void printNumColunas(int Quantidade_Casas, int ncolunas) {
  for (int m = 0; m < ncolunas; m++) {
    int Quantidade_Casas_Coluna = contaCasasNumero(m);
    printf(" ");
    for (int n = 0; n < Quantidade_Casas - Quantidade_Casas_Coluna; n++) {
      printf(" ");
    }
    printf("%d ", m);
  }
  printf("\n");
}

void estabeleceNumVaga(estacionamento **E, int nlinhas, int ncolunas) {
  int numerovaga = 1;
  for (int i = 0; i < nlinhas; i++) {
    for (int j = 0; j < ncolunas; j++) {
      if (E[i][j].Status_Vaga != -1) {
        E[i][j].numVaga = numerovaga;
        numerovaga++;
      }
    }
  }
}

void modelagemEstacionamento(estacionamento **E, int nlinha1, int nlinha2,
                             int ncoluna1, int ncoluna2, int nlinhaMAX,
                             int ncolunaMAX, int operador) {
  consertaPosicoesInvalidas(nlinhaMAX, ncolunaMAX, &nlinha1, &nlinha2,
                            &ncoluna1, &ncoluna2);
  organizaNumero(&nlinha1, &nlinha2);
  organizaNumero(&ncoluna1, &ncoluna2);
  for (int i = nlinha1; i <= nlinha2; i++) {
    for (int j = ncoluna1; j <= ncoluna2; j++) {
      // Vagape comum
      if (operador == 1 && E[i][j].Status_Vaga != -1) {
        E[i][j].Tipo_Vaga = 0;
      }
      // Vaga para pessoa idosa
      else if (operador == 2 && E[i][j].Status_Vaga != -1) {
        E[i][j].Tipo_Vaga = 1;
      }
      // Vaga para pessoa portadora de alguma deficiencia
      else if (operador == 3 && E[i][j].Status_Vaga != -1) {
        E[i][j].Tipo_Vaga = 2;
      }

      // Vaga VIP
      else if (operador == 4 && E[i][j].Status_Vaga != -1) {
        E[i][j].Tipo_Vaga = 3;
      }
      // Vaga inexistente
      else if (operador == 5) {
        E[i][j].Status_Vaga = -1;
        E[i][j].numVaga = -1;
      }
      // Vaga em manutencao
      else if (operador == 6 && E[i][j].Status_Vaga != -1) {
        E[i][j].Status_Vaga = 3;
      }
      // Reconstroi a vaga
      else if (operador == 7 && E[i][j].Status_Vaga == -1) {
        E[i][j].Status_Vaga = 0;
      }
      else if(operador == 8 && E[i][j].Status_Vaga == 3){
        E[i][j].Status_Vaga = 0;
      }
    }
  }
  // Caso vagas sejam retirada ou resconstruidas seus numero precisam ser
  // alterados
  if (operador == 4 || operador == 7) {
    estabeleceNumVaga(E, nlinhaMAX, ncolunaMAX);
  }
}

void consertaPosicoesInvalidas(int nlinhas, int ncolunas, int *nlinha1,
                               int *nlinha2, int *ncoluna1, int *ncoluna2) {
  // Conserta Numeros que estao acima do valor correto
  if (*nlinha1 >= nlinhas)
    *nlinha1 = nlinhas - 1;
  if (*nlinha2 >= nlinhas)
    *nlinha2 = nlinhas - 1;
  if (*ncoluna1 >= ncolunas)
    *ncoluna1 = ncolunas - 1;
  if (*ncoluna2 >= ncolunas)
    *ncoluna2 = ncolunas - 1;
  // Conserta Numeros que estao a baixo do valor correto
  if (*nlinha1 < 0)
    *nlinha1 = 0;
  if (*nlinha2 < 0)
    *nlinha2 = 0;
  if (*ncoluna1 < 0)
    *ncoluna1 = 0;
  if (*ncoluna2 < 0)
    *ncoluna2 = 0;
}

// Função Vitin para Info

void estacionamentoInfo(estacionamento **E, int ncolunas, int nlinhas, int *nv,
                        int *nvd, int *nvi, int *nvv) {
  if (E == NULL) return;
  *nvd = 0;
  *nvi = 0;
  *nvv = 0;
  *nv = 0;
  int z;
  for (int l = 0; l < nlinhas; l++) {
    for (int c = 0; c < ncolunas; c++) {
      if (E[l][c].Status_Vaga != -1) {
        z = E[l][c].Tipo_Vaga;
        switch (z) {
        case 1:
          // pessoa portadora de deficiencia
          *nvd += 1;
          break;
        case 2:
          // idoso
          *nvi += 1;
          break;
        case 3:
          // vip
          *nvv += 1;
          break;
        case 0:
          // comum
          *nv += 1;
          break;
        }
      }
    }
  }
  int numerovaga = 0;
  for (int i = 0; i < nlinhas; i++) {
    for (int j = 0; j < ncolunas; j++) {
      if (E[i][j].Status_Vaga != -1) {
        E[i][j].numVaga = numerovaga;
        numerovaga++;
      }
    }
  }
}

void estacionamentoLegenda(){
  printf("\n\n");
  printf(ANSI_COLOR_WHITE"● Vaga comum Livre\n");
  printf(ANSI_COLOR_RED"● Vaga comum Ocupada\n");
  printf(ANSI_COLOR_BLUE"● Vaga idoso Livre\n");
  printf(ANSI_COLOR_MAGENTA"● Vaga idoso Ocupada\n");
  printf(ANSI_COLOR_YELLOW"● Vaga para pessoa portadora de deficiencia Livre\n");
  printf(ANSI_COLOR_ORANGE"● Vaga para pessoa portadora de deficiencia Ocupada\n");
  printf(ANSI_COLOR_GREEN"● Vaga VIP Livre\n");
  printf(ANSI_COLOR_GREEN2"● Vaga VIP Ocupada\n");
  printf(ANSI_COLOR_YELLOW"/"ANSI_COLOR_WHITE"/ Vaga em Manutencao\n\n");
  printf(ANSI_COLOR_WHITE);
}

int buscaVagaLivreDeficiente(estacionamento **E, int nlinhas, int ncolunas){
  int numVagaLivreDeficiente;
  for(int i = 0; i < nlinhas; i++){
    for(int j = 0; j < ncolunas; j++){
      if(E[i][j].Tipo_Vaga == 1 && E[i][j].Status_Vaga == 0){
        numVagaLivreDeficiente = E[i][j].numVaga;
        return numVagaLivreDeficiente;
      }
    }
  }
  //Caso não exista vaga livre
  return -1;
}

int buscaVagaLivreIdoso(estacionamento **E, int nlinhas, int ncolunas){
  int numVagaLivreIdoso;
  for(int i = 0; i < nlinhas; i++){
    for(int j = 0; j < ncolunas; j++){
      if(E[i][j].Tipo_Vaga == 2 && E[i][j].Status_Vaga == 0){
        numVagaLivreIdoso = E[i][j].numVaga;
        return numVagaLivreIdoso;
      }
    }
  }
  //Caso não exista vaga livre
  return -1;
}

int buscaVagaLivreVip(estacionamento **E, int nlinhas, int ncolunas){
  int numVagaLivreIdoso;
  for(int i = 0; i < nlinhas; i++){
    for(int j = 0; j < ncolunas; j++){
      if(E[i][j].Tipo_Vaga == 3 && E[i][j].Status_Vaga == 0){
        numVagaLivreIdoso = E[i][j].numVaga;
        return numVagaLivreIdoso;
      }
    }
  }
  //Caso não exista vaga livre
  return -1;
}

int buscaVagaLivreComum(estacionamento **E, int nlinhas, int ncolunas){
  int numVagaLivreIdoso;
  for(int i = 0; i < nlinhas; i++){
    for(int j = 0; j < ncolunas; j++){
      if(E[i][j].Tipo_Vaga == 0 && E[i][j].Status_Vaga == 0){
        numVagaLivreIdoso = E[i][j].numVaga;
        return numVagaLivreIdoso;
      }
    }
  }
  //Caso não exista vaga livre
  return -1;
}

int buscaVagaLivre(estacionamento **E, int nlinhas, int ncolunas){
  int numVagaLivreIdoso;
  for(int i = 0; i < nlinhas; i++){
    for(int j = 0; j < ncolunas; j++){
      if(E[i][j].Status_Vaga == 1){
        return 1;
      }
    }
  }
  //Caso não exista vaga livre
  return -1;
}

estacionamento *procuraV(estacionamento **E, int nlinhas, int ncolunas, int p){
    estacionamento *Vaga;
    for(int i = 0; i < nlinhas; i++){
        for(int j = 0; j < ncolunas; j++){
          if(E[i][j].numVaga == p){
            return &(E[i][j]);
      }
    }
  }
}

void alteraStatus(estacionamento **E, int nlinhas, int ncolunas, int numvaga, int status){
    //a int status muda para 0 ou 1 caso o usuario entre ou saia dela
    for(int i = 0; i < nlinhas; i++){
        for(int j = 0; j < ncolunas; j++){
          if(E[i][j].numVaga == numvaga) E[i][j].Status_Vaga = status;
    }
  }
}

void InfoVaga(estacionamento **E, int nlinhas, int ncolunas, int p, int *num, int *tip, int *stat){
    estacionamento *Vaga;
    for(int i = 0; i < nlinhas; i++){
        for(int j = 0; j < ncolunas; j++){
            if(E[i][j].numVaga == p){
                Vaga = &(E[i][j]);
      }
    }
  }
  *num = Vaga->numVaga;
  *tip = Vaga->Tipo_Vaga;
  *stat = Vaga->Status_Vaga;
   return ;
}
