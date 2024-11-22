#include "listaencadeada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// cria a lista encadeada a ser usada;
ListaEncadeada *criarLista() {
  ListaEncadeada *lista = (ListaEncadeada *)malloc(sizeof(ListaEncadeada));
  lista->inicio = NULL;
  return lista;
}

// funcao para alocar o novo cadastro
Motorista *criarM() {
  Motorista *t = (Motorista *)malloc(sizeof(Motorista));
  if (t == NULL)
    exit(1);
  return t;
}


// pausa o programa ate clicar enter

// motoristas j� cadastrados
void inicilizarMotor(ListaEncadeada *lista) {
  Motorista *motor1 = criarM();
  strcpy(motor1->nome, "Joao");
  strcpy(motor1->cpf, "12345678900");
  strcpy(motor1->placa, "ABC1234");
  strcpy(motor1->email, "987654321");
  strcpy(motor1->senha, "senha123");
  motor1->senha[strcspn(motor1->senha, "\n")] = '\0';
  strcpy(motor1->prioridade, "N�o possui");
  motor1->adm = 1;
  motor1->dentro = 0;

  Motorista *motor2 = criarM();
  strcpy(motor2->nome, "Maria");
  strcpy(motor2->cpf, "98765432100");
  strcpy(motor2->placa, "DEF5678");
  strcpy(motor2->email, "123456789");
  strcpy(motor2->senha, "senha456");
  motor2->senha[strcspn(motor2->senha, "\n")] = '\0';
  strcpy(motor2->prioridade, "Idoso");
  motor2->adm = 0;
  motor2->dentro = 0;

  Motorista *motor3 = criarM();
  strcpy(motor3->nome, "Pedro");
  strcpy(motor3->cpf, "56789012300");
  strcpy(motor3->placa, "GHI9012");
  strcpy(motor3->email, "987654321");
  strcpy(motor3->senha, "senha789");
  motor3->senha[strcspn(motor3->senha, "\n")] = '\0';
  strcpy(motor3->prioridade, "Idoso");
  motor3->adm = 0;
  motor3->dentro = 0;

  Motorista *motor4 = criarM();
  strcpy(motor4->nome, "Ana");
  strcpy(motor4->cpf, "23456789011");
  strcpy(motor4->placa, "JKL3456");
  strcpy(motor4->email, "654321987");
  strcpy(motor4->senha, "senha101112");
  motor4->senha[strcspn(motor4->senha, "\n")] = '\0';
  strcpy(motor4->prioridade, "Idoso");
  motor4->adm = 0;
  motor4->dentro = 0;

  Motorista *motor5 = criarM();
  strcpy(motor5->nome, "Carlos");
  strcpy(motor5->cpf, "45678901222");
  strcpy(motor5->placa, "MNO6789");
  strcpy(motor5->email, "321654987");
  strcpy(motor5->senha, "senha131415");
  motor5->senha[strcspn(motor5->senha, "\n")] = '\0';
  strcpy(motor5->prioridade, "N�o possui");
  motor5->adm = 0;
  motor5->dentro = 0;

  Motorista *motor6 = criarM();
  strcpy(motor6->nome, "Raquel");
  strcpy(motor6->cpf, "67890123433");
  strcpy(motor6->placa, "PQR1234");
  strcpy(motor6->email, "789456123");
  strcpy(motor6->senha, "senha161718");
  motor6->senha[strcspn(motor6->senha, "\n")] = '\0';
  strcpy(motor6->prioridade, "PCD");
  motor6->adm = 0;
  motor6->dentro = 0;

  Motorista *motor7 = criarM();
  strcpy(motor7->nome, "Lucas");
  strcpy(motor7->cpf, "90123456744");
  strcpy(motor7->placa, "STU5678");
  strcpy(motor7->email, "456123789");
  strcpy(motor7->senha, "senha192021");
  motor7->senha[strcspn(motor7->senha, "\n")] = '\0';
  strcpy(motor7->prioridade, "N�o possui");
  motor7->adm = 0;
  motor7->dentro = 0;

  Motorista *motor8 = criarM();
  strcpy(motor8->nome, "Julia");
  strcpy(motor8->cpf, "12345098755");
  strcpy(motor8->placa, "VWX9012");
  strcpy(motor8->email, "987123654");
  strcpy(motor8->senha, "senha222324");
  motor8->senha[strcspn(motor8->senha, "\n")] = '\0';
  strcpy(motor8->prioridade, "VIP");
  motor8->adm = 0;
  motor8->dentro = 0;

  Motorista *motor9 = criarM();
  strcpy(motor9->nome, "Fernanda");
  strcpy(motor9->cpf, "34567890166");
  strcpy(motor9->placa, "YZA3456");
  strcpy(motor9->email, "789321654");
  strcpy(motor9->senha, "senha252627");
  motor9->senha[strcspn(motor9->senha, "\n")] = '\0';
  strcpy(motor9->prioridade, "N�o possui");
  motor9->adm = 0;
  motor9->dentro = 0;

  Motorista *motor10 = criarM();
  strcpy(motor10->nome, "Ricardo");
  strcpy(motor10->cpf, "56789012377");
  strcpy(motor10->placa, "BCD5678");
  strcpy(motor10->email, "654987321");
  strcpy(motor10->senha, "senha282930");
  motor10->senha[strcspn(motor10->senha, "\n")] = '\0';
  strcpy(motor10->prioridade, "N�o possui");
  motor10->adm = 0;
  motor10->dentro = 0;

  Motorista *motor11 = criarM();
  strcpy(motor11->nome, "Zephyrus");
  strcpy(motor11->cpf, "56789012379");
  strcpy(motor11->placa, "BCD5678");
  strcpy(motor11->email, "zephyr@example");
  strcpy(motor11->senha, "senha111213");
  motor11->senha[strcspn(motor11->senha, "\n")] = '\0';
  strcpy(motor11->prioridade, "N�o possui");
  motor11->adm = 0;
  motor11->dentro = 0;

  Motorista *motor12 = criarM();
  strcpy(motor12->nome, "Athena");
  strcpy(motor12->cpf, "12345678900");
  strcpy(motor12->placa, "DEF1234");
  strcpy(motor12->email, "athena@ex.com");
  strcpy(motor12->senha, "senha141516");
  motor12->senha[strcspn(motor12->senha, "\n")] = '\0';
  strcpy(motor12->prioridade, "Idoso");
  motor12->adm = 0;
  motor12->dentro = 0;

  Motorista *motor13 = criarM();
  strcpy(motor13->nome, "Lysander");
  strcpy(motor13->cpf, "98765432100");
  strcpy(motor13->placa, "GHI5678");
  strcpy(motor13->email, "lysander@ex.co");
  strcpy(motor13->senha, "senha171819");
  motor13->senha[strcspn(motor13->senha, "\n")] = '\0';
  strcpy(motor13->prioridade, "PCD");
  motor13->adm = 0;
  motor13->dentro = 0;

  Motorista *motor14 = criarM();
  strcpy(motor14->nome, "Elysia");
  strcpy(motor14->cpf, "45678912300");
  strcpy(motor14->placa, "JKL9012");
  strcpy(motor14->email, "elysia@examp");
  strcpy(motor14->senha, "senha202122");
  motor14->senha[strcspn(motor14->senha, "\n")] = '\0';
  strcpy(motor14->prioridade, "VIP");
  motor14->adm = 0;
  motor14->dentro = 0;

  Motorista *motor15 = criarM();
  strcpy(motor15->nome, "Xanthe");
  strcpy(motor15->cpf, "65432198700");
  strcpy(motor15->placa, "MNO3456");
  strcpy(motor15->email, "xanthe@ex.com");
  strcpy(motor15->senha, "senha232425");
  motor15->senha[strcspn(motor15->senha, "\n")] = '\0';
  strcpy(motor15->prioridade, "N�o possui");
  motor15->adm = 0;
  motor15->dentro = 0;

  Motorista *motor16 = criarM();
  strcpy(motor16->nome, "Zephyr");
  strcpy(motor16->cpf, "32165498700");
  strcpy(motor16->placa, "PQR7890");
  strcpy(motor16->email, "zephyr@ex.com");
  strcpy(motor16->senha, "senha262728");
  motor16->senha[strcspn(motor16->senha, "\n")] = '\0';
  strcpy(motor16->prioridade, "N�o possui");
  motor16->adm = 0;
  motor16->dentro = 0;

  Motorista *motor17 = criarM();
  strcpy(motor17->nome, "Luna");
  strcpy(motor17->cpf, "78901234567");
  strcpy(motor17->placa, "STU1234");
  strcpy(motor17->email, "luna@ex.com");
  strcpy(motor17->senha, "senha293031");
  motor17->senha[strcspn(motor17->senha, "\n")] = '\0';
  strcpy(motor17->prioridade, "N�o possui");
  motor17->adm = 0;
  motor17->dentro = 0;

  Motorista *motor18 = criarM();
  strcpy(motor18->nome, "Leo");
  strcpy(motor18->cpf, "90123456789");
  strcpy(motor18->placa, "VWX5678");
  strcpy(motor18->email, "leo@ex.com");
  strcpy(motor18->senha, "senha323334");
  motor18->senha[strcspn(motor18->senha, "\n")] = '\0';
  strcpy(motor18->prioridade, "N�o possui");
  motor18->adm = 0;
  motor18->dentro = 0;

  Motorista *motor19 = criarM();
  strcpy(motor19->nome, "Aurora");
  strcpy(motor19->cpf, "34567890123");
  strcpy(motor19->placa, "YZA9012");
  strcpy(motor19->email, "aurora@ex.com");
  strcpy(motor19->senha, "senha353637");
  motor19->senha[strcspn(motor19->senha, "\n")] = '\0';
  strcpy(motor19->prioridade, "N�o possui");
  motor19->adm = 0;
  motor19->dentro = 0;

  Motorista *motor20 = criarM();
  strcpy(motor20->nome, "Orion");
  strcpy(motor20->cpf, "56789012345");
  strcpy(motor20->placa, "BCD3456");
  strcpy(motor20->email, "orion@ex.com");
  strcpy(motor20->senha, "senha383940");
  motor20->senha[strcspn(motor20->senha, "\n")] = '\0';
  strcpy(motor20->prioridade, "N�o possui");
  motor20->adm = 0;
  motor20->dentro = 0;

  Motorista *motor21 = criarM();
  strcpy(motor21->nome, "Gava");
  strcpy(motor21->cpf, "98765432109");
  strcpy(motor21->placa, "QWERTY1");
  strcpy(motor21->email, "motorista21@example.com");
  strcpy(motor21->senha, "senha456");
  motor21->senha[strcspn(motor21->senha, "\n")] = '\0';
  strcpy(motor21->prioridade, "N�o possui");
  motor21->adm = 0;
  motor21->dentro = 0;

  inserirMotorista(lista, motor1);
  inserirMotorista(lista, motor2);
  inserirMotorista(lista, motor3);
  inserirMotorista(lista, motor4);
  inserirMotorista(lista, motor5);
  inserirMotorista(lista, motor6);
  inserirMotorista(lista, motor7);
  inserirMotorista(lista, motor8);
  inserirMotorista(lista, motor9);
  inserirMotorista(lista, motor10);
  inserirMotorista(lista, motor11);
  inserirMotorista(lista, motor12);
  inserirMotorista(lista, motor13);
  inserirMotorista(lista, motor14);
  inserirMotorista(lista, motor15);
  inserirMotorista(lista, motor16);
  inserirMotorista(lista, motor17);
  inserirMotorista(lista, motor18);
  inserirMotorista(lista, motor19);
  inserirMotorista(lista, motor20);
  inserirMotorista(lista, motor21);
}

// insere o novo cadastro na lista, ou coloca como primeiro elemento se a lista
// esta vazia
void inserirMotorista(ListaEncadeada *lista, Motorista *novoMotorista) {
  // cria um novo n� com o motrista a ser inserido
  No *novoNo = (No *)malloc(sizeof(No));
  novoNo->valor = novoMotorista;
  novoNo->ant = NULL;
  novoNo->prox = NULL;

  if (lista->inicio == NULL) {
    // se a lista estiver vazia, o novo no se torna o primeiro da lista
    lista->inicio = novoNo;
  } else {
    // percorre a lista at� o �ltimo no e insere o novo n� no final, se a lista
    // nao estiver vazia
    No *atual = lista->inicio;
    while (atual->prox != NULL) {
      atual = atual->prox;
    }
    atual->prox = novoNo;
    novoNo->ant = atual;
  }
}

// fun��o para verificar qual o valor da variavel "adm do cadastro a ser lido
int checaAdm(No *atual) {
  if (atual->valor->adm == 1)
    return 1;
  else
    return 0;
}

int Login(ListaEncadeada *lista, char *cpf,
          char *senha) { // faz o login, checando nas listas o cpf e senha
  No *atual = lista->inicio;
  while (atual != NULL) {
    if (strcmp(atual->valor->cpf, cpf) == 0) {
      if (strcmp(atual->valor->senha, senha) == 0) {
        if (checaAdm(atual) == 1) { // Mudar para 1 para funcionar normalmente,
          return 1;
        }
        return 2;
      }
    }
    atual = atual->prox;
  }
  return 3;
}

// funcao para promover cadastro ja criado a adm
void NovoAdm(ListaEncadeada *lista, char *cpf) {
  No *novoadm = NULL;
  novoadm = procuraM(lista, cpf);
  if (novoadm != NULL) {
    novoadm->valor->adm = 1;
  }
}

// funcao que busca cadastro correspondente ao inserido e exclui o mesmo
int excluirMotor(ListaEncadeada *lista, char *cpf) {
  No *atual = lista->inicio;
  No *encontrado = NULL;
  encontrado = procuraM(lista, cpf);
  if (encontrado != NULL) {
    if (encontrado->ant == NULL) {
      lista->inicio = encontrado->prox; // motorista eh o primeiro da lista
      if (encontrado->prox != NULL) {
        atual = encontrado->ant;
        atual->prox = NULL;
      }
    } else if (encontrado->prox == NULL) {
      atual = encontrado->ant;
      atual->prox = NULL; // motoristaeh o ultimo da lista
    } else {              // motorista a ser exclu�do ta no meio da lista
      atual = encontrado->ant;
      atual->prox = encontrado->prox;
      atual = encontrado->prox;
      atual->ant = encontrado->ant;
    }
    free(encontrado);
    return 1;
  }
  return 0;
}

int editarSenha(ListaEncadeada *lista, char *cpf, char *novaS) {
  No *encontrado = NULL;
  encontrado = procuraM(lista, cpf);
  if (encontrado != NULL) {
    strcpy(encontrado->valor->senha, novaS);
    return 1;
  }
  return 0;
}

No *procuraM(ListaEncadeada *lista, char *cpf1) {
  No *atual = lista->inicio;
  while (atual != NULL) {
    if (strcmp(atual->valor->cpf, cpf1) == 0) {
      return atual;
    }
    atual = atual->prox;
  }
  return NULL;
}


Lista *criarK() {
  Lista *l = (Lista *)malloc(sizeof(Lista));
  l->inicio = NULL;
  return l;
}

int listaVazia(Lista *l) {
  if (l == NULL)
    return 2;
  if (l->inicio == NULL)
    return 0;
  return 1;
}

int inserirInicio(Lista *l, Motorista pessoa) {
  if (l == NULL)
    return 2;
  No1 *No = (No1 *)malloc(sizeof(No1));
  No->valor = pessoa;
  No->prox = l->inicio;
  l->inicio = No;
  return 0;
}

int inserirFim(Lista *l, Motorista pessoa) {
  if (l == NULL)
    return 2;
  if (listaVazia(l) == 0)
    return inserirInicio(l, pessoa);
  No1 *No1Lista = l->inicio;
  while (No1Lista->prox != NULL)
    No1Lista = No1Lista->prox;
  No1 *No = (No1 *)malloc(sizeof(No1));
  No->valor = pessoa;
  No->prox = No1Lista->prox;
  No1Lista->prox = No;
  return 0;
}

int inserirPosicao(Lista *l, Motorista pessoa, int pos) {
  if (l == NULL)
    return 2;
  if (pos < 0)
    return 3;
  if ((listaVazia(l) == 0) || (pos == 0))
    return inserirInicio(l, pessoa);
  No1 *No1Lista = l->inicio;
  int p = 1;
  while ((No1Lista->prox != NULL) && (p != pos)) {
    p++;
    No1Lista = No1Lista->prox;
  }
  No1 *No = (No1 *)malloc(sizeof(No1));
  No->valor = pessoa;
  No->prox = No1Lista->prox;
  No1Lista->prox = No;
  return 0;
}

int removerInicio(Lista *l) {
  if (l == NULL)
    return 2;
  if (listaVazia(l) == 0)
    return 1;
  No1 *No1Lista = l->inicio;
  l->inicio = No1Lista->prox;
  free(No1Lista);
  return 0;
}

int removerFim(Lista *l) {
  if (l == NULL)
    return 2;
  if (listaVazia(l) == 0)
    return 1;
  No1 *No1Auxiliar = NULL;
  No1 *No1Lista = l->inicio;
  while (No1Lista->prox != NULL) {
    No1Auxiliar = No1Lista;
    No1Lista = No1Lista->prox;
  }
  if (No1Auxiliar == NULL) {
    l->inicio = NULL;
  } else {
    No1Auxiliar->prox = NULL;
  }
  free(No1Lista);
  return 0;
}

int buscarItemCpf(Lista *l, char *cpf, Motorista *retorNo1) {
  int i;
  int verifica = 0;
  if (l == NULL)
    return 2;
  No1 *No1Lista = l->inicio;
  while ((No1Lista != NULL)) {
    for (i = 0; i < 12; i++) {
      if (No1Lista->valor.cpf[i] != cpf[i])
        verifica = 1;
    }
    if (verifica == 0) {
      *retorNo1 = No1Lista->valor;
      return 0;
    }
    No1Lista = No1Lista->prox;
  }
  return 1;
}

void limparK(Lista *l) {
  while (listaVazia(l) != 0)
    removerInicio(l);
}

void mostrarK(Lista *l) {
  if (l != NULL) {
    printf("[");
    No1 *No1Lista = l->inicio;
    while (No1Lista != NULL) {
      printf("{%s,", No1Lista->valor.nome);
      printf("%s,", No1Lista->valor.cpf);
      printf("%s,", No1Lista->valor.placa);
      printf("%s,", No1Lista->valor.email);
      printf("%s,", No1Lista->valor.senha);
      printf("%s,", No1Lista->valor.prioridade);
      printf("%d,", No1Lista->valor.vagaocupada);
      printf("%d,", No1Lista->valor.dentro);
      printf("%d}", No1Lista->valor.adm);
      No1Lista = No1Lista->prox;
    }
    printf("]\n");
  }
}

int tamanhoK(Lista *l) {
  int t = 0;
  if (l == NULL)
    return -1;
  if (listaVazia(l) == 0)
    return 0;
  No1 *No1Lista = l->inicio;
  while (No1Lista->prox != NULL) {
    No1Lista = No1Lista->prox;
    t++;
  }
  return t;
}

int removerItem(Lista *l, int numVaga) {
  int verifica = 0;
  int i;
  if (l == NULL)
    return 2;
  if (listaVazia(l) == 0)
    return 1;
  No1 *No1Auxiliar = NULL;
  No1 *No1Lista = l->inicio;
  while ((No1Lista != NULL)) {
    if (No1Lista->valor.vagaocupada == numVaga)
      verifica = 1;
    if (verifica == 0) {
      if (No1Auxiliar == NULL) {
        l->inicio = NULL;
      } else {
        No1Auxiliar->prox = No1Lista->prox;
      }
      free(No1Lista);
      return 0;
    }
    No1Auxiliar = No1Lista;
    No1Lista = No1Lista->prox;
  }
  return 0;
}

// é considerada a nossa 'fila' e l1 é o estacionamento em lista
void alocarMotoristaEstacionamento(Lista *l, Lista *l1, Motorista *pessoa, estacionamento **E, int nlinhas, int ncolunas) {
  int retornoVaga, status;
  if (l == NULL) {
    l = criarK();
  }
  if (l1 == NULL) {
    l1 = criarK();
  }
  if (strcmp(pessoa->prioridade, "Idoso") == 0) {
    retornoVaga = buscaVagaLivreIdoso(E, nlinhas, ncolunas);
    status = 1;
  } else if (strcmp(pessoa->prioridade, "PCD") == 0) {
    retornoVaga = buscaVagaLivreDeficiente(E, nlinhas, ncolunas);
    status = 1;
  } else if (strcmp(pessoa->prioridade, "VIP") == 0) {
    retornoVaga = buscaVagaLivreVip(E, nlinhas, ncolunas);
    status = 1;
  }

  if (retornoVaga == -1) {
    retornoVaga = buscaVagaLivreComum(E, nlinhas, ncolunas);
    status = 1;
  }
  // Se o retornoVaga for == -1 tem que colocar o motoriasta na lista de espera
  if (retornoVaga == -1) {
    alocarMotoristaFila(l, pessoa);
    return;
  }
  pessoa->vagaocupada = retornoVaga;
  if(inserirFim(l1, *pessoa) == 0){
    pessoa->dentro = 1;
  }
  alteraStatus(E, nlinhas, ncolunas, retornoVaga, status);
  return;
}

void alocarMotoristaFila(Lista *l, Motorista *pessoa) {
  if (listaVazia(l) == 0) {
    inserirInicio(l, *pessoa);
    return;
  }
  No1 *no = l->inicio;
  No1 *noAuxiliar = NULL;
  No1 *noMotorista = (No1 *)malloc(sizeof(No1));
  noMotorista->valor = *pessoa;
  if (strcmp(pessoa->prioridade, "PCD") == 0) {
    while (strcmp(no->prox->valor.prioridade, "PCD") == 0) {
      noAuxiliar = no;
      no = no->prox;
    }
    noAuxiliar->prox = noMotorista;
    noMotorista->prox = no;
  } else if (strcmp(pessoa->prioridade, "Idoso") == 0) {
    while (strcmp(no->prox->valor.prioridade, "Idoso") == 0 ||
           strcmp(no->prox->valor.prioridade, "PCD") == 0) {
      noAuxiliar = no;
      no = no->prox;
    }

  } else if (strcmp(pessoa->prioridade, "VIP") == 0) {
    while (strcmp(no->prox->valor.prioridade, "Idoso") == 0 ||
           strcmp(no->prox->valor.prioridade, "PCD") == 0 ||
           strcmp(no->prox->valor.prioridade, "VIP") == 0) {
      noAuxiliar = no;
      no = no->prox;
    }
  } else {
    while (no != NULL) {
      noAuxiliar = no;
      no = no->prox;
    }
    noAuxiliar->prox = noMotorista;
    noMotorista->prox = no;
  }
}

void filaParaEstacionamento(Lista *l, Lista *l1, estacionamento **E, int nlinhas, int ncolunas) {
  No1 *no = l->inicio;
  Motorista *pessoa = &no->valor;
  alocarMotoristaEstacionamento(l, l1, pessoa, E, nlinhas, ncolunas);
  l->inicio = no->prox;
}

void liberarVaga(estacionamento **E, Lista *l1, Motorista *pessoa, int nlinhas, int ncolunas, int numeroVaga) {
  int status = 0;
  removerItem(l1, numeroVaga);
  alteraStatus(E, nlinhas, ncolunas, numeroVaga, status);
  pessoa->dentro = 0;
}
