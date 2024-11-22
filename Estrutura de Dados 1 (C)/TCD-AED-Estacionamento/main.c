#include "Estacionamento.h"
#include "listaencadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_WHITE "\x1b[0m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_YELLOW "\x1b[93m"

// Funções da lista encadeada

// Funções de cadastros
void imprimirMotoristas(Motorista *impresso);
void imprimeALL(ListaEncadeada *lista);
int Loginn(ListaEncadeada *lista);
Motorista *criaM(int adm, ListaEncadeada *listaU);
void gerenciarCadastro(ListaEncadeada *lista);
int strinTparaI(char *priori);
char cpfL[12];

// Pausa para não sumir os prints antes de apertar enter
void pause();
// Funções Básicas de user
void user(estacionamento **E, ListaEncadeada *listaU, int nlinhas, int ncolunas,
          float precoHora, Lista *L, Lista *L1, float precoVIP,
          float Fidelidade);

// Funções básicas de ADM
estacionamento **ADM(estacionamento **E, float *precoHora, float *precoVIP,
                     int *retornoNlinhas, int *retornoNcolunas,
                     ListaEncadeada *listaU, Lista *l, Lista *l1,
                     float *Fidelidade);
char admMenu(estacionamento **E);
void admDemostracao(estacionamento **E, int nlinhas, int ncolunas);
void admModelagem(estacionamento **E, int nlinhas, int ncolunas);
float admPrecoHora();
float admPrecoVIP();
float admFidelidade();
void admLei(estacionamento **E, int numTotVagas, int numDefi);

void inserirTodosEstacionamento(Lista *l, Lista *l1, ListaEncadeada *l2,
                                estacionamento **E, int nlinhas, int ncolunas);
void removeTodosEstacionamento(estacionamento **E, Lista *l, Lista *l1,
                               int nlinhas, int ncolunas);

float Timer();
float contaTempo(int dia1, int dia2, int hora1, int hora2, int min1, int min2);

int main() {
  int nlinhas, ncolunas;
  // Adicionar libera estacionamento
  estacionamento **E = NULL;
  ListaEncadeada *listaU = criarLista();
  Lista *l = criarK();
  Lista *l1 = criarK();

  inicilizarMotor(listaU);
  char Op;
  float precoHora, precoVIP, Fidelidade;
  int adm;
  int primeira = 0;
  int out = 1;
  while (out) {
    system("clear");
    printf("~Login do Estacionamento\n\n");
    printf("[1]: Criar Cadastro \n");
    printf("[2]: Logar \n");
    printf("[3]: Sair\n-> ");
    setbuf(stdin, NULL);
    scanf(" %c", &Op);
    switch (Op) {
    case '1':
      inserirMotorista(listaU, criaM(0, listaU));
      break;
    case '2':
      adm = Loginn(listaU);
      if (adm == 2) {
        if (primeira) {
          user(E, listaU, nlinhas, ncolunas, precoHora, l, l1, precoVIP,
               Fidelidade);
        } else {
          printf("O Adminstrador precisa inicializar o estacionamento\n");
        }
      } else if (adm == 1) {
        E = ADM(E, &precoHora, &precoVIP, &nlinhas, &ncolunas, listaU, l, l1,
                &Fidelidade);
        if (E != NULL)
          primeira = 1;
      } else if (adm == 0) {
        printf("Login Incorreto\n");
        pause();
      }
      break;
    case '3':
      out = 0;
      break;
    }
  }
}

void user(estacionamento **E, ListaEncadeada *listaU, int nlinhas, int ncolunas,
          float precoHora, Lista *L, Lista *L1, float precoVIP,
          float Fidelidade) {
  No *logado;
  logado = procuraM(listaU, cpfL);
  int vagaNaoEncontrada = 1;
  char op, op2;
  char priori[15];
  float precoTotal, time;
  int v, tP;
  do {
    system("clear");
    printf("~Menu usuario\n\n");
    printf("[1]: Entrar no estacionamento\n");
    printf("[2]: Excluir seu cadastro\n");
    printf("[3]: Comprar VIP\n");
    printf("[4]: Sair\n-> ");
    setbuf(stdin, NULL);
    scanf(" %c", &op);
    strcpy(priori, logado->valor->prioridade);
    tP = strinTparaI(priori);
    switch (op) {
    case '1':
      //
      if (tP == 0)
        v = -1;
      if (tP == 2) {
        v = buscaVagaLivreDeficiente(E, nlinhas, ncolunas);
        if (v == -1)
          vagaNaoEncontrada = -1;
        else {
          system("clear");
          printf("A vaga [%d] está livre, se dirija a ela\n", v);
        }
      }
      if (tP == 1) {
        v = buscaVagaLivreIdoso(E, nlinhas, ncolunas);
        if (v == -1)
          vagaNaoEncontrada = -1;
        else {
          system("clear");
          printf("A vaga [%d] está livre, se dirija a ela\n", v);
        }
      }
      if (tP == 3) {
        v = buscaVagaLivreVip(E, nlinhas, ncolunas);
        if (v == -1)
          vagaNaoEncontrada = -1;
        else {
          system("clear");
          printf("A vaga [%d] está livre, se dirija a ela\n", v);
        }
      }
      if (vagaNaoEncontrada == -1) {
        v = buscaVagaLivreComum(E, nlinhas, ncolunas);
        if (v == -1)
          vagaNaoEncontrada = -1;
        else {
          system("clear");
          printf("A vaga [%d] está livre, se dirija a ela\n", v);
        }
      }
      // Aloca o motorista no estacionamento, caso não há vaga, aloca na lista
      alocarMotoristaEstacionamento(L, L1, logado->valor, E, nlinhas, ncolunas);
      tP = strinTparaI(priori);
      // Funcoes que calculam o valor a ser pago
      time = Timer();
      if (tP == 3) {
        precoTotal = time * precoHora * Fidelidade;
      } else {
        precoTotal = time * precoHora;
      }
      printf("O total a ser pago e R$ %.2f\n", precoTotal);
      pause();
      alteraStatus(E, nlinhas, ncolunas, v, 0);
      liberarVaga(E, L1, logado->valor, nlinhas, ncolunas, v);
      break;
    case '2':
      if (excluirMotor(listaU, cpfL)) {
        printf("Cadastro excluido\n");
      } else {
        printf("Erro ao excluir cadastro\n");
      }
      break;
    case '3':
      do {
        system("clear");
        printf("Desejar comprar VIP (R$ %.2f)\n", precoVIP);
        printf("O valor da cobranca sera reduzido para %.2f\n", Fidelidade);
        printf("[1]: Comprar\n");
        printf("[2]: Sair\n-> ");
        scanf(" %c", &op2);
        if (op2 == '1')
          strcpy(logado->valor->prioridade, "VIP");
      } while (op2 != '2' && op2 != '1');
      break;
    }
  } while (op != '4' && op != '2');
  // mostrarL(listaE);
}

estacionamento **ADM(estacionamento **E, float *precoHora, float *precoVIP,
                     int *retornoNlinhas, int *retornoNcolunas,
                     ListaEncadeada *listaU, Lista *l, Lista *l1,
                     float *Fidelidade) {
  // variaveis que contam a quatniade de tipos de vaga
  int TESTEVAGAS;
  int nv, nvi, nvd, nvv, totVagas;
  char Op;
  int nlinhas, ncolunas;
  int nlinha1, ncoluna1, nlinha2, ncoluna2;
  // variavel declarada como preço 0 caso o estacionamento não tenha preço Ex.:
  // Patio de carros
  *precoHora = 0;
  *precoVIP = 0;
  do {
    // Print do menu das funcoes de ADM
    Op = admMenu(E);
    // Opcoes do ADM
    switch (Op) {
    case '1':
      // Condicao que verfica se o estacionamento pode ser refeito ou não
      if (E != NULL) {
        int estacionamentoLivre;
        estacionamentoLivre = buscaVagaLivre(E, nlinhas, ncolunas);
        // Condicao caso o estacionamento não esteja livre
        if (estacionamentoLivre == 1) {
          printf(ANSI_COLOR_YELLOW
                 "Existem pessoas no estacionamento, nenhuma alteracao pode "
                 "ser feita!\n\n" ANSI_COLOR_WHITE);
          pause();
          break;
        } else
          liberaEstacionamento(E, *retornoNlinhas);
      }
      printf("Escreva a quantidade de linhas: ");
      scanf("%d", &nlinhas);
      printf("Escreva a quantidade de colunas: ");
      scanf("%d", &ncolunas);
      *retornoNlinhas = nlinhas;
      *retornoNcolunas = ncolunas;
      E = criarEstacionamento(nlinhas, ncolunas);
      printf("\n\n");
      break;
    case '2':
      if (E != NULL) {
        int estacionamentoLivre;
        estacionamentoLivre = buscaVagaLivre(E, nlinhas, ncolunas);
        // Condicao caso o estacionamento não esteja livre
        if (estacionamentoLivre == 1) {
          printf(ANSI_COLOR_YELLOW
                 "Existem pessoas no estacionamento, nenhuma alteracao pode "
                 "ser feita!\n\n" ANSI_COLOR_WHITE);
          pause();
          break;
        }
      }
      admModelagem(E, nlinhas, ncolunas);
      break;
    case '3':
      system("clear");
      printEstacionamento(E, nlinhas, ncolunas);
      pause();
      break;
    case '4':
      system("clear");
      // Imprime informações do estacionamento
      estacionamentoInfo(E, ncolunas, nlinhas, &nv, &nvd, &nvi, &nvv);
      totVagas = nv + nvd + nvi + nvv;
      if (E == NULL)
        break;
      printf("Numero total de vagas: %d\n", totVagas);
      printf("Vagas comuns: %d\n", nv);
      printf("Vagas para pessoas portadoras de deficiencia: %d\n", nvd);
      printf("Vagas para pessoas idosas: %d\n", nvi);
      printf("Vagas VIPs: %d\n\n", nvv);
      // Funcao que confere as normas de estacionamento segundo a lei n° 13.146
      admLei(E, totVagas, nvd);
      pause();
      break;
    case '5':
      if (E == NULL)
        break;
      *precoHora = admPrecoHora();
      *precoVIP = admPrecoVIP();
      *Fidelidade = admFidelidade();
      pause();
      break;
    case '6':
      // Criacao do estacionamento para demonstração,
      // Todas as operações são executadas para que facilite a aprensatação para
      // o professor
      // Condicao que verfica se o estacionamento pode ser refeito ou não
      if (E != NULL) {
        int estacionamentoLivre;
        estacionamentoLivre = buscaVagaLivre(E, nlinhas, ncolunas);
        // Condicao caso o estacionamento não esteja livre
        if (estacionamentoLivre == 1) {
          printf(ANSI_COLOR_YELLOW
                 "Existem pessoas no estacionamento, nenhuma alteracao pode "
                 "ser feita!\n\n" ANSI_COLOR_WHITE);
          pause();
          break;
        }
      } else {
        liberaEstacionamento(E, *retornoNlinhas);
      }

      nlinhas = 5;
      ncolunas = 11;
      *retornoNlinhas = nlinhas;
      *retornoNcolunas = ncolunas;
      E = criarEstacionamento(nlinhas, ncolunas);
      admDemostracao(E, nlinhas, ncolunas);
      break;
    case '7':
      gerenciarCadastro(listaU);
      break;
    case '8':
      if (E == NULL)
        break;
      inserirTodosEstacionamento(l, l1, listaU, E, nlinhas, ncolunas);
      // Crirar funcao de adicionar todo mundo no estacionamento
      break;
    case '9':
      if (E == NULL)
        break;
      removeTodosEstacionamento(E, l, l1, nlinhas, ncolunas);
      // removeTodosEstacionamento(estacionamento **E, Lista *l1, int nlinhas,
      // int ncolunas)
    }
  } while (Op != '0');
  return E;
}

char admMenu(estacionamento **E) {
  // Print do menu das funcoes de ADM
  char Op;
  system("clear");
  printf("~Menu:\n\n");
  printf("[1]: Criar Estacionamento\n");
  if (E == NULL)
    printf(ANSI_COLOR_RED);
  printf("[2]: Modelar Estacionamento\n");
  printf("[3]: Mostrar Estacionamento\n");
  printf("[4]: Info\n");
  printf("[5]: Adicionar Precos\n");
  printf(ANSI_COLOR_WHITE);
  printf("[6]: Demonstracao\n");
  printf("[7]: Menu de Cadastros\n");
  if (E == NULL)
    printf(ANSI_COLOR_RED);
  printf("[8]: Colocar os usuarios (Demonstracao)\n");
  printf("[9]: Retirar os usuarios (Demonstracao)\n");
  printf(ANSI_COLOR_WHITE);
  printf("[0]: Sair\n");
  printf("-> ");
  scanf(" %c", &Op);
  printf("\n\n");
  return Op;
}

void admModelagem(estacionamento **E, int nlinhas, int ncolunas) {
  system("clear");
  if (E == NULL)
    return;
  int nlinha1, nlinha2, ncoluna1, ncoluna2, operador;
  printEstacionamento(E, nlinhas, ncolunas);
  printf("\nPosicao 1° linha: ");
  scanf(" %d", &nlinha1);
  printf("Posicao 2° linha: ");
  scanf(" %d", &nlinha2);
  printf("Posicao 1° coluna: ");
  scanf(" %d", &ncoluna1);
  printf("Posicao 2° coluna: ");
  scanf(" %d", &ncoluna2);

  printf("\n[1]: Vaga comum\n");
  printf("[2]: Vaga para pessoa portadora de deficiencia\n");
  printf("[3]: Vaga para idosos\n");
  printf("[4]: Vaga VIP\n");
  printf("[5]: Eliminar vaga\n");
  printf("[6]: Vaga em manutencao\n");
  printf("[7]: Restaurar Vagas\n");
  printf("[8]: Retira vaga do estado de manutencao\n\n");
  printf("Opcao: ");
  scanf(" %d", &operador);
  printf("\n\n");

  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
  printEstacionamento(E, nlinhas, ncolunas);
}

float admPrecoHora() {
  float preco;
  printf("Preco por hora: R$ ");
  scanf(" %f", &preco);
  return preco;
}

float admPrecoVIP() {
  float preco;
  printf("Preco por mes de VIP R$ ");
  scanf(" %f", &preco);
  return preco;
}

void admDemostracao(estacionamento **E, int nlinhas, int ncolunas) {
  int nlinha1, nlinha2, ncoluna1, ncoluna2, operador;

  // Modelagem pronta
  nlinha1 = 2;
  nlinha2 = 2;
  ncoluna1 = 0;
  ncoluna2 = 10;
  operador = 5;
  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
  nlinha1 = 0;
  nlinha2 = 4;
  ncoluna1 = 3;
  ncoluna2 = 3;
  operador = 5;
  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
  nlinha1 = 0;
  nlinha2 = 4;
  ncoluna1 = 7;
  ncoluna2 = 7;
  operador = 5;
  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
  nlinha1 = 0;
  nlinha2 = 0;
  ncoluna1 = 0;
  ncoluna2 = 3;
  operador = 3;
  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
  nlinha1 = 0;
  nlinha2 = 0;
  ncoluna1 = 4;
  ncoluna2 = 6;
  operador = 2;
  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
  nlinha1 = 0;
  nlinha2 = 1;
  ncoluna1 = 8;
  ncoluna2 = 10;
  operador = 4;
  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
  nlinha1 = 4;
  nlinha2 = 4;
  ncoluna1 = 0;
  ncoluna2 = 10;
  operador = 6;
  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
  nlinha1 = 3;
  nlinha2 = 3;
  ncoluna1 = 0;
  ncoluna2 = 2;
  operador = 6;
  modelagemEstacionamento(E, nlinha1, nlinha2, ncoluna1, ncoluna2, nlinhas,
                          ncolunas, operador);
}

void admLei(estacionamento **E, int numTotVagas, int numDefi) {
  if (E == NULL)
    return;
  printf("O estacionamento esta de acordo com a lei: ");
  if (numTotVagas <= 100) {
    if (numDefi == 0) {
      printf(ANSI_COLOR_RED "x\n");
    } else {
      printf(ANSI_COLOR_GREEN "✔\n");
    }
  } else {
    int numMinimoVagaDefi;
    numMinimoVagaDefi = numTotVagas * 0.02;
    if (numDefi < numMinimoVagaDefi) {
      printf(ANSI_COLOR_RED "x\n");
    } else {
      printf(ANSI_COLOR_GREEN "✔\n");
    }
  }
  printf(ANSI_COLOR_WHITE "\n\n");
}

void pause() {
  char c;
  printf("Escreva qualquer caracter e pressione 'Enter' para continuar\n");
  scanf(" %c", &c);
}

// Funções de gerenciar cadastros

int Loginn(ListaEncadeada *lista) {
  char cpf[12];
  char senha[12];
  int out = 1;
  // pede CPF e senha ao usu�rio
  printf("Digite o CPF: ");
  setbuf(stdin, NULL);
  scanf(" %s", cpf);

  printf("Digite a senha: ");
  setbuf(stdin, NULL);
  scanf(" %s", senha);
  senha[strcspn(senha, "\n")] = '\0';
  int l;
  l = Login(lista, cpf, senha);
  switch (l) {
  case 1:
    printf("Login feito pelo administrador\n");
    strcpy(cpfL, cpf);
    return 1;
    out = 0;
    break;
  case 2:
    printf("Login feito pelo usuario\n");
    strcpy(cpfL, cpf);
    return 2;
    out = 0;
    break;
  case 3:
    printf("Login nao encontrado\n");
    return 0;
    break;
  }
}

Motorista *criaM(int adm, ListaEncadeada *listaU) {
  char opPrio, op1, op;
  Motorista *novoMot = criarM();
  No *aux;
  printf("Digite o nome: \n");
  setbuf(stdin, NULL);
  getchar();
  fgets(novoMot->nome, 30, stdin);
  novoMot->nome[strcspn(novoMot->nome, "\n")] = '\0';

  printf("Digite o CPF: \n");
  setbuf(stdin, NULL);
  fgets(novoMot->cpf, 12, stdin);
  getchar();
  novoMot->cpf[strcspn(novoMot->cpf, "\n")] = '\0';
  aux = procuraM(listaU, novoMot->cpf);
  if (aux != NULL) {
    printf("Usuario ja Cadastrado\n");
    return NULL;
  }

  printf("Digite a placa do veiculo: \n");
  setbuf(stdin, NULL);
  fgets(novoMot->placa, 8, stdin);
  getchar();
  novoMot->placa[strcspn(novoMot->placa, "\n")] = '\0';

  printf("Digite o email: \n");
  setbuf(stdin, NULL);
  fgets(novoMot->email, 30, stdin);
  getchar();
  novoMot->email[strcspn(novoMot->email, "\n")] = '\0';

  printf("Digite a senha: \n");
  setbuf(stdin, NULL);
  fgets(novoMot->senha, 13, stdin);
  novoMot->senha[strcspn(novoMot->senha, "\n")] = '\0';

  printf("Possui prioridade?\n[S/N]\n-> ");
  setbuf(stdin, NULL);
  scanf(" %c", &op1);
  if (op1 == 'N' || op1 == 'n') {
    strcpy(novoMot->prioridade, "N�o possui");
  } else {
    if (op1 == 'S' || op1 == 's') {
      do {
        printf("Selecione seu tipo de prioridade:\n[1] - Idoso\n[2] - PCD "
               "(Pessoa Com Deficiencia\n-> ");
        scanf(" %c", &opPrio);
        switch (opPrio) {
        case '1':
          strcpy(novoMot->prioridade, "Idoso");
          printf("Prioridade cadastrada com sucesso!\n");
          break;
        case '2':
          strcpy(novoMot->prioridade, "PCD");
          printf("Prioridade cadastrada com sucesso!\n");
          break;
        default:
          printf("Opcao invalida!\n");
        }

      } while (opPrio != '1' && opPrio != '2');
    }
  }
  novoMot->dentro = 0; // nao esta estacionado
  if (adm) {
    printf("Quer definir esse cadastro como um adm?(S/N)\n-> ");
    setbuf(stdin, NULL);
    scanf(" %c", &op);
    if (op == 'S' || op == 's') {
      novoMot->adm = 1;
      printf("\nCadastro salvo como adm!\n");
      pause();
    } else {
      if (op == 'N' || op == 'n') {
        novoMot->adm = 0;
        printf("\nCadastro salvo normalmente!\n");
        pause();
      } else {
        printf("\nEntrada invalida!\n");
        pause();
      }
    }
  } else {
    novoMot->adm = 0; // define como usuario normal
  }
  return novoMot;
}

void imprimirMotoristas(Motorista *impresso) {
  printf("-Nome: %s\n", impresso->nome);
  printf("-CPF: %s\n", impresso->cpf);
  printf("-Placa do veiculo: %s\n", impresso->placa);
  printf("-Email: %s\n", impresso->email);
  printf("-Senha: %s\n", impresso->senha);
  printf("-Prioridade: %s\n", impresso->prioridade);
  printf("-Administrador: %d\n", impresso->adm);
  printf("-Dentro: %d\n", impresso->dentro);
  printf("\n");
}

void imprimeALL(ListaEncadeada *lista) {
  No *atual = lista->inicio;
  while (atual != NULL) {
    imprimirMotoristas(atual->valor);
    atual = atual->prox;
  }
}

void gerenciarCadastro(ListaEncadeada *lista) {
  int opcao;
  int out = 1;
  char cpf[12];
  char novaS[12];
  // print12(lista);
  while (out) {
    printf("~Gerenciador de Cadastros\n");
    printf("[1]: Cadastrar novo motorista\n");
    printf("[2]: Cadastrar novo administrador\n");
    printf("[3]: Excluir Cadastro de Motorista\n");
    printf("[4]: Editar Senha de motoristas cadastrados\n");
    printf("[5]: Imprimir motoristas cadastrados\n");
    printf("[6]: Voltar ao Menu inicial\n");
    printf("-> ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      system("clear");
      printf("Opcao selecionada: Cadastrar novo motorista\n");
      inserirMotorista(lista, criaM(0, lista));
      system("clear");
      break;
    case 2:
      system("clear");
      printf("Opcao selecionada: Cadastrar novo administrador\n");
      inserirMotorista(lista, criaM(1, lista));
      system("clear");
      break;
    case 3:
      system("clear");
      printf("Opcao selecionada: Excluir Cadastro de Motorista\n");
      printf("Digite o cpf do motorista que deseja excluir\n-> ");
      setbuf(stdin, NULL);
      fgets(cpf, 12, stdin);
      printf("%s", cpf);
      if (excluirMotor(lista, cpf)) {
        break;
      } else {
        printf("CPF nao encontrado tente novamente");
      }
    case 4:
      system("clear");
      printf("Opcao selecionada: Editar Senha de motoristas cadastrados\n");
      printf("Digite o cpf do motorista que deseja editar\n-> ");
      setbuf(stdin, NULL);
      fgets(cpf, 12, stdin);
      printf("Digite a senha do motorista que deseja editar\n-> ");
      setbuf(stdin, NULL);
      fgets(novaS, 12, stdin);
      if (editarSenha(lista, cpf, novaS)) {
        break;
      } else {
        printf("CPF nao encontrado tente novamente");
      }
    case 5:
      system("clear");
      printf("Opcao selecionada: Imprimir motoristas cadastrados\n");
      imprimeALL(lista);
      pause();
      system("clear");
      break;
    case 6:
      system("clear");
      printf("Opcao selecionada: Voltar ao Menu inicial\n");
      pause();
      out = 0;
      break;
    default:
      printf("Opcao invalida!\n");
      system("clear");
    }
    printf("\n");
    printf("Terminou");
  }
}

int strinTparaI(char *priori) {
  if (strcmp(priori, "Nao possui") == 0) {
    return 0;
  } else if (strcmp(priori, "Idoso") == 0) {
    return 1;
  } else if (strcmp(priori, "PCD") == 0) {
    return 2;
  } else if (strcmp(priori, "VIP") == 0) {
    return 3;
  }
}

float Timer() {
  time_t t1 = time(NULL);
  // Recebe os valores do horario de entrada
  struct tm InicioTimer = *localtime(&t1);

  // Ajuste dos valores devido ao fuso
  InicioTimer.tm_year = InicioTimer.tm_year + 1900;
  InicioTimer.tm_mon = InicioTimer.tm_mon + 1;
  InicioTimer.tm_hour = InicioTimer.tm_hour - 3;

  printf("Data atual = %d/%02d/%02d\n", InicioTimer.tm_year, InicioTimer.tm_mon,
         InicioTimer.tm_mday);
  printf("Horario de entrada = %d:%d\n\n", InicioTimer.tm_hour,
         InicioTimer.tm_min);
  pause();

  time_t t2 = time(NULL);
  // Recebe os valores do horario de saida
  struct tm FimTimer = *localtime(&t2);

  // Ajuste dos valores devido ao fuso
  FimTimer.tm_hour = FimTimer.tm_hour - 3;
  printf("Horario de saida = %d:%d\n", FimTimer.tm_hour, FimTimer.tm_min);

  float qthora =
      contaTempo(InicioTimer.tm_mday, FimTimer.tm_mday, InicioTimer.tm_hour,
                 FimTimer.tm_hour, InicioTimer.tm_min, FimTimer.tm_min);
  printf("Tempo de permanencia: %.2f hora(s)\n", qthora);
  return qthora;
}

float contaTempo(int dia1, int dia2, int hora1, int hora2, int min1, int min2) {
  float qtdia, qthora, qtmin;
  qtdia = dia2 - dia1;
  qthora = hora2 - hora1;
  qtmin = min2 - min1;

  if (qtdia < 0)
    qthora = qthora + 24;
  if (qtmin > 0)
    qthora++;
  if (qtmin < 0)
    qthora--;

  qtdia = qtdia * 24;
  qthora = qthora + qtdia;
  return qthora;
}

// l é a lista de espera
// l1 é a lista de dentro do estacionamento
// l2 é a lista de cadastros
// Funcao feita apenas para colocar pessoas dentro do estacionamento para a
// apresentação do trabalho
void inserirTodosEstacionamento(Lista *l, Lista *l1, ListaEncadeada *l2,
                                estacionamento **E, int nlinhas, int ncolunas) {
  if (l2 == NULL) {
    printf("Erro!\n");
    return;
  }
  No *no = l2->inicio;
  while (no != NULL) {
    Motorista *pessoa = no->valor;
    alocarMotoristaEstacionamento(l, l1, pessoa, E, nlinhas, ncolunas);
    no = no->prox;
  }
}

// Funcao feita apenas para remover pessoas dentro do estacionamento para a
// apresentação do trabalho
void removeTodosEstacionamento(estacionamento **E, Lista *l, Lista *l1,
                               int nlinhas, int ncolunas) {
  int numeroVaga;
  No1 *no = l1->inicio;
  No1 *nol = l->inicio;
  while (no != NULL) {
    Motorista *pessoa = &no->valor;
    numeroVaga = pessoa->vagaocupada;
    liberarVaga(E, l1, pessoa, nlinhas, ncolunas, numeroVaga);
    no = no->prox;
  }
  while (nol != NULL) {
    filaParaEstacionamento(l, l1, E, nlinhas, ncolunas);
    nol = nol->prox;
  }
}

int verPosicaoNaFila(Lista *l, char *cpf) {
  int posicao = 1;
  No1 *no = l->inicio;
  while (no != NULL) {
    if (strcmp(no->valor.cpf, cpf) == 0) {
      return posicao;
    }
    no = no->prox;
  }
  return -1;
}

float admFidelidade() {
  float Fidelidade;
  printf("Escolha a quantidade de desconto:\n");
  printf("Exemplo: 0.8 o motorista ganha 20%% de desconto valor total.\n");
  scanf(" %f", &Fidelidade);
  if (Fidelidade > 1)
    Fidelidade = 1;
  else if (Fidelidade < 0)
    Fidelidade = 0;
  return Fidelidade;
}