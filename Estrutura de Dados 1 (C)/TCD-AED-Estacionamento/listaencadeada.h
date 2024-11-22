#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>c
#include "Estacionamento.h"

//estrutura de dados para motorista, com suas variaveis
typedef struct motorista {
    char nome[30];
    char cpf[12]; // usado para login
    char placa[8];
    char email[30];
    char senha[13]; // para login
    char prioridade[15]; // classica qual tipo de prioridade o cadastro pode se encaixar: Idoso, PCD ou VIP
    int vagaocupada;
    int dentro; // veiculo dentro do estacionamento
    int adm; // verifica se cadastro � de adm, se for true(1) ou sim, o usuario entra direto no menu de ADM
} Motorista;

typedef struct No1 {
  Motorista valor;
  struct No1 *prox;
} No1;

typedef struct lista {
  No1 *inicio;
} Lista;

typedef struct No {
    Motorista* valor;
    struct No* prox;
    struct No* ant;
} No;

typedef struct listaencadeada{
    Motorista valor;
    No* inicio;
    No* fim;
} ListaEncadeada;


//funcoes principais
int menuInicial(ListaEncadeada* lista);


//fun��o de print
void Menu();

//definitivas
int editarSenha(ListaEncadeada* lista, char *cpf, char *novaS);
int excluirMotor(ListaEncadeada* lista, char *cpf);
void NovoAdm(ListaEncadeada* lista, char *cpf);
int checaAdm(No* atual);
void inserirMotorista(ListaEncadeada* lista, Motorista* novoMotorista);
No *procuraM(ListaEncadeada* lista, char *cpf);
int Login(ListaEncadeada* lista, char *cpf, char *senha);
void inicilizarMotor(ListaEncadeada* lista);

//cria��o de dados
ListaEncadeada* criarLista();
Motorista *criarM();

typedef struct lista Lista;
Lista *criarK();
void limparK(Lista *l);
int inserirInicio(Lista *l,Motorista pessoa);
int inserirFim(Lista *l,Motorista pessoa);
int inserirPosicao(Lista*l,Motorista pessoa,int pos);
int removerInicio(Lista *l);
int removerFim(Lista *l);
int removerItem(Lista *l,int NumVaga);
int buscarItemCpf(Lista *l,char *cpf,Motorista *retorno);
int listaVazia(Lista *l);
int tamanhoK(Lista *l);
void mostrarK(Lista *l);

void alocarMotoristaEstacionamento(Lista *l, Lista *l1, Motorista *pessoa,estacionamento **E, int nlinhas, int ncolunas);//aloca um motorista em uma vaga
void alocarMotoristaFila(Lista *l, Motorista *pessoa);//aloca um motorista na fila caso esteja lotado o estacionamento
void filaParaEstacionamento(Lista *l, Lista *l1,estacionamento **E, int nlinhas, int ncolunas);
void liberarVaga(estacionamento **E, Lista *l1 , Motorista *pessoa, int nlinhas, int ncolunas,int numeroVaga);
//motorista vai da fila para o estacionamento
