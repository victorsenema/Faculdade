#include <stdio.h>
// biblioteca de manipulação de string;
#include <string.h>
// biblioteca com funções uteis relacionadas a tipos e outros;
#include <stdlib.h>
// biblioteca usada para maniplução de tempo;
#include <time.h>
// Função my_sleep, para adicionar delay nas informações
#if defined(_WIN32)
#define WINDOWS_SYSTEM
#include <Windows.h>
#else
#define UNIX_SYSTEM
#include <unistd.h>
#endif

// Variáveis de COR
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[92m"
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_COLOR_RESET "\x1b[0m"

void my_sleep(int sleepms);
void Nome_Jogador(char *nome);
void Jogar();
void Regras();
void Rank();
void Sobre();
void Distribui_Cartas(int cartas[6]);
void Printa_Placar(int Pontuacao_P1, int Pontuacao_P2, int Placar_Rodadas_Resultado[3], int Valor);
void Printa_Naipes(int Carta_Recebida);
void Printa_Cartas_Player(int C1_P2, int C2_P2, int C3_P2, int Carta_Jogada_P2, int Bolean_Carta_P2, int Jogadas_P2, int Pontuacao_P2, int Pontuacao_P1);
void Printa_Cartas_Bot(int Bolean_Carta_P1, int Numero_Cartas_P1, int Carta_Jogada_P1);
void Pedir_Truco_Tipo_1(int *Valor_Rodada_Tipo1, int *Check_Player_Plus_Tento_Tipo1, int *Ganhador_Tento_Tipo1, int *Tipo_Usado_Tipo1);
void Pedir_Truco_Tipo_2(int *Valor_Rodada_Tipo2, int *Check_Player_Plus_Tento_Tipo2, int *Ganhador_Tento_Tipo2, int *Tipo_Usado_Tipo2);
int Resultado_Rodada(int Carta_Jogada_P1, int Carta_Jogada_P2, int *Vencedor_Rodada);
int Forca_Carta(int Valor_Carta);
int Forca_Cartas_Bot(int Carta1, int Carta2, int Carta3);
int Bot_IA_Truco(); // Precisa Escrever
int Bot_IA(int R1, int Carta_JogadaP2, int media, int *Player_K, int R_Atual, int carta_farca, int carta_media, int carta_forte, int carta_jogada1, int carta_jogada2, int Bot_Joga_Primeiro, int Pontuacao1, int Pontuacao2);
void Historia_Vitoria();
void Historia_Derrota();
void AddRank(int Ganhou,int Perdeu,char *nome);

void main()
{
  // Operador do menu
  int op;

  do
  {
    system("clear");
    printf("=====================°------°=====================\n");
    printf("§ § § § § § § § § § §| Menu | § § § § § § § § § § \n");
    printf("=====================°------°=====================\n");
    printf("                ¤ Truco Faroeste ¤\n");
    printf("====================°--------°====================\n");
    printf("                    |1-Jogar |\n");
    printf("                    |2-Rank  |\n");
    printf("                    |3-Regras|\n");
    printf("                    |4-Sobre |\n");
    printf("                    |5-Sair  |\n");
    printf("                    |--------|\n");
    printf("==================================================\n");
    printf("                     Opcao: ");
    scanf("%d", &op);
    getchar();
    fflush(stdin);
    switch (op)
    {
    case 1:
      Jogar();
      break;
    case 2:
      Rank();
      break;
    case 3:
      Regras();
      break;
    case 4:
      Sobre();
      break;
    }
  } while (op != 5);

  system("pause");
}

void Jogar()
{
  char *nome_player;
  nome_player = (char *)malloc(sizeof(char) * 30);
  // Função para pegar o nome do jogador;
  Nome_Jogador(nome_player);
  // Booleano para repetiçaõ do jogo caso o jogador escolha jogar novamente;
  int Jogar_Novamente = 1;
  // Vetor que recebe valor das cartas, de 0 - 2 é o Player 1(Bot), 3 - 6 é o Player 2
  int Player_C[6];
  // Contador de rodadas ganahs por jogador
  int Rodada_PontuacaoP1, Rodada_PontuacaoP2;
  // Carta escolhida pelo Jogador 2;
  int Player2_C_Atual, Player2_C_Bolean, Player2_Bolean, Player2_Jogadas, Player2_Pontuacao = 0;
  int Player1_C_Atual, Player1_C_Bolean, Player1_Bolean, P1_Numero_Cartas, Player1_Pontuacao = 0;
  int Tipo_Truco;
  int Vencedor_Tento;
  int Vencedor_Rodada;
  int Plus_Tento;
  int Valor_da_Rodada;
  int Aux_Carta_Bot, Aux_Carta_P2;
  int Ganhou2, Perdeu2;
  int n; // Numero de carta escolhido pelo jogador
  int Placar_Rodadas_Resultado[3];
  int Contador_Rodadas;
  int InicioTento, contador_tento;
  int Forca_IA;
  int N_Rodada, Resultado_R1;
  int Bot_Carta_Jogada1, Bot_Carta_Jogada2;
  int Bot_IA_Carta_P2;
  srand(time(NULL));

  // DO PARTIDA => JOGAR NOVAMENTE?
  do
  {
    Ganhou2 = 0;
    Perdeu2 = 0;
    contador_tento = 0;
    Player1_Pontuacao = 0;
    Player2_Pontuacao = 0;
    InicioTento = 2;
    // DO TENTO => RODA A CADA TENTO
    do
    {
      // Marca a pontuação de cada jogador. Quando chegar a >= 6 (2 vitórias), o jogador Ganha. Caso contrário, ganha quem marcar mais. VITÓRIA = 3pts, EMPATE = 1.
      switch(InicioTento){
        case 1:
          InicioTento = 2;
        break;
        case 2:
          InicioTento = 1;
        break;
      }
      Rodada_PontuacaoP1 = 0;
      Rodada_PontuacaoP2 = 0;
      N_Rodada = 0;
      Bot_Carta_Jogada1 = 0;
      Bot_Carta_Jogada2 = 0;
      Valor_da_Rodada = 12;

      // Placar de rodadas ganha por tento. VERDE = vitória, VERMELHOR = derrota, AMARELO = empate.
      Placar_Rodadas_Resultado[0] = -1;
      Placar_Rodadas_Resultado[1] = -1;
      Placar_Rodadas_Resultado[2] = -1;

      // ======= DEFINE QUEM JOGA PRIMEIRO NO TENTO ======= //

      if (Vencedor_Tento == 0)
      {
        Player1_Bolean = 0;
        Player2_Bolean = 0;
      }
      // Se o BOT ganhou o último TENTO, quem joga é ele
      else if (Vencedor_Tento == 1)
      {
        Player1_Bolean = 1;
        Player2_Bolean = 0;
      }
      // Se o PLAYER ganhou o último TENTO, quem joga é ele
      else if (Vencedor_Tento == 2)
      {
        Player1_Bolean = 0;
        Player2_Bolean = 1;
      }

      // Vencedor por rodada. 1 = Bot, 2 = Player, 3 = Empate
      Vencedor_Rodada = 0;

      // Distribuir cartas. 0,1 e 2 = Cartas Bot. 3, 4, 5 = Cartas Player
      Distribui_Cartas(Player_C);
      //Função que Analisa a Força das cartas que serão usadas na Ia do Bot
      Forca_IA = Forca_Cartas_Bot(Player_C[0], Player_C[1], Player_C[2]);

      // Quantas jogadas o Player 2 fez
      Player2_Jogadas = 0;

      P1_Numero_Cartas = 3;

      Contador_Rodadas = 0;

      // Setup inicial. 3 cartas Bot, 3 cartas Player
      Printa_Placar(Player1_Pontuacao, Player2_Pontuacao, Placar_Rodadas_Resultado, Valor_da_Rodada);
      Printa_Cartas_Bot(0, P1_Numero_Cartas, -1);
      Printa_Cartas_Player(Player_C[3], Player_C[4], Player_C[5], Player2_C_Atual, Player2_C_Bolean, Player2_Jogadas, Player2_Pontuacao, Player1_Pontuacao);
      my_sleep(1000);

      // Vencedor por tento. 1 = Bot, 2 = Player, 3 = Empate
      Vencedor_Tento = 0;
      // DO CADA RODADA
      do
      {
        N_Rodada += 1;
        // ======= DEFINE QUEM JOGA PRIMEIRO NA RODADA ======= //

        // Reseta as cartas jogadas anteriormente
        Player1_C_Bolean = 0;
        Player2_C_Bolean = 0;

        // Imprime mesa sem cartas jogadas
        Printa_Placar(Player1_Pontuacao, Player2_Pontuacao, Placar_Rodadas_Resultado, Valor_da_Rodada);
        Printa_Cartas_Bot(0, P1_Numero_Cartas, -1);
        Printa_Cartas_Player(Player_C[3], Player_C[4], Player_C[5], Player2_C_Atual, Player2_C_Bolean, Player2_Jogadas, Player2_Pontuacao, Player1_Pontuacao);
        my_sleep(1000);

        // Se o BOT ganhou a última RODADA, quem joga é ele
        if (Vencedor_Rodada == 0 && (Player1_Pontuacao == 0 && Player2_Pontuacao == 0))
        {
          Player1_Bolean = 0;
          Player2_Bolean = 1;
        }
        if (Vencedor_Rodada == 1)
        {
          Player1_Bolean = 0;
          Player2_Bolean = 1;
        }
        // Se o PLAYER ganhou a última RODADA, quem joga é ele
        else if (Vencedor_Rodada == 2)
        {
          Player1_Bolean = 1;
          Player2_Bolean = 0;
        }

        if (InicioTento == 1)
        {
          Aux_Carta_Bot = Bot_IA(Resultado_R1, Bot_IA_Carta_P2, Forca_IA, Player_C,  N_Rodada, Player_C[0], Player_C[1], Player_C[2],Bot_Carta_Jogada1, Bot_Carta_Jogada2, Player1_Bolean, Player1_Pontuacao, Player2_Pontuacao);

          if(N_Rodada == 1){
            Bot_Carta_Jogada1 = Aux_Carta_Bot;
          }
          if(N_Rodada == 2){
            Bot_Carta_Jogada2 = Aux_Carta_Bot;
          }
          Player1_C_Atual = Player_C[Aux_Carta_Bot];
          P1_Numero_Cartas -= 1;
          Player_C[Aux_Carta_Bot] = -1;
          Player1_C_Bolean = 1;
          Printa_Placar(Player1_Pontuacao, Player2_Pontuacao, Placar_Rodadas_Resultado, Valor_da_Rodada);
          Printa_Cartas_Bot(Player1_C_Bolean, P1_Numero_Cartas, Player1_C_Atual);
          Printa_Cartas_Player(Player_C[3], Player_C[4], Player_C[5], Player2_C_Atual, Player2_C_Bolean, Player2_Jogadas, Player2_Pontuacao, Player1_Pontuacao);
          my_sleep(1000);

          // Funcionalidade de pedir Truco
          if (Player1_Pontuacao != 11 && Player2_Pontuacao == 11)
          {
            if (Tipo_Truco == 1 || Tipo_Truco == 0)
            {
              Pedir_Truco_Tipo_1(Valor_da_Rodada, Plus_Tento, Vencedor_Tento, Tipo_Truco);
            }
            if (Tipo_Truco == 2 || Tipo_Truco == 0)
            {
              Pedir_Truco_Tipo_2(Valor_da_Rodada, Plus_Tento, Vencedor_Tento, Tipo_Truco);
            }
          }

          // VERIFICAR SE CARTA DIGITADA EXISTE ENTRE AS OPÇÕES
          do
          {
            printf("Qual carta jogar? ");
            scanf("%d", &n);
            Player2_Bolean = 1;
            Aux_Carta_P2 = n + 2;
            Player2_C_Atual = Player_C[Aux_Carta_P2];
            Bot_IA_Carta_P2 = Player_C[Aux_Carta_P2];

            if(Player2_C_Atual == -1 || n > 3 || n < 1)
            {
              printf("Opcao invalida. Tente novamente.");
            }
          } while (Player2_C_Atual == -1 || n > 3 || n < 1);
          Player_C[Aux_Carta_P2] = -1;
          Player2_C_Bolean = 1;
          
          if (Aux_Carta_P2 == 3)
          {
            Player2_Jogadas += 1;
          }
          if (Aux_Carta_P2 == 4)
          {
            Player2_Jogadas += 6;
          }
          if (Aux_Carta_P2 == 5)
          {
            Player2_Jogadas += 3;
          }

          Printa_Placar(Player1_Pontuacao, Player2_Pontuacao, Placar_Rodadas_Resultado, Valor_da_Rodada);
          Printa_Cartas_Bot(Player1_C_Bolean, P1_Numero_Cartas, Player1_C_Atual);
          Printa_Cartas_Player(Player_C[3], Player_C[4], Player_C[5], Player2_C_Atual, Player2_C_Bolean, Player2_Jogadas, Player2_Pontuacao, Player1_Pontuacao);
          my_sleep(1000);
        }
        else if (InicioTento == 2)
        {
          Printa_Placar(Player1_Pontuacao, Player2_Pontuacao, Placar_Rodadas_Resultado, Valor_da_Rodada);
          Printa_Cartas_Bot(Player1_C_Bolean, P1_Numero_Cartas, Player1_C_Atual);
          Printa_Cartas_Player(Player_C[3], Player_C[4], Player_C[5], Player2_C_Atual, Player2_C_Bolean, Player2_Jogadas, Player2_Pontuacao, Player1_Pontuacao);
          // Funcionalidade de pedir Truco
          if (Player1_Pontuacao != 11 && Player2_Pontuacao == 11)
          {
            if (Tipo_Truco == 1 || Tipo_Truco == 0)
            {
              Pedir_Truco_Tipo_1(Valor_da_Rodada, Plus_Tento, Vencedor_Tento, Tipo_Truco);
            }
            if (Tipo_Truco == 2 || Tipo_Truco == 0)
            {
              Pedir_Truco_Tipo_2(Valor_da_Rodada, Plus_Tento, Vencedor_Tento, Tipo_Truco);
            }
          }
          // VERIFICAR SE CARTA DIGITADA EXISTE ENTRE AS OPÇÕES
          do
          {
            printf("Qual carta jogar? ");
            scanf("%d", &n);
            Player2_Bolean = 1;
            Aux_Carta_P2 = n + 2;
            Player2_C_Atual = Player_C[Aux_Carta_P2];
            Bot_IA_Carta_P2 = Player_C[Aux_Carta_P2];

            if(Player2_C_Atual == -1 || n > 3 || n < 1)
            {
              printf("Opcao invalida. Tente novamente.");
            }
          } while (Player2_C_Atual == -1 || n > 3 || n < 1);
          Player_C[Aux_Carta_P2] = -1;
          Player2_C_Bolean = 1;
          
          if (Aux_Carta_P2 == 3)
          {
            Player2_Jogadas += 1;
          }
          if (Aux_Carta_P2 == 4)
          {
            Player2_Jogadas += 6;
          }
          if (Aux_Carta_P2 == 5)
          {
            Player2_Jogadas += 3;
          }

          Printa_Placar(Player1_Pontuacao, Player2_Pontuacao, Placar_Rodadas_Resultado, Valor_da_Rodada);
          Printa_Cartas_Bot(Player1_C_Bolean, P1_Numero_Cartas, Player1_C_Atual);
          Printa_Cartas_Player(Player_C[3], Player_C[4], Player_C[5], Player2_C_Atual, Player2_C_Bolean, Player2_Jogadas, Player2_Pontuacao, Player1_Pontuacao);
          my_sleep(1000);

          Aux_Carta_Bot = Bot_IA(Resultado_R1, Bot_IA_Carta_P2, Forca_IA, Player_C,  N_Rodada, Player_C[0], Player_C[1], Player_C[2],Bot_Carta_Jogada1, Bot_Carta_Jogada2, Player1_Bolean, Player1_Pontuacao, Player2_Pontuacao);
          if(N_Rodada == 1){
            Bot_Carta_Jogada1 = Aux_Carta_Bot;
          }
          if(N_Rodada == 2){
            Bot_Carta_Jogada2 = Aux_Carta_Bot;
          }
          Player1_C_Atual = Player_C[Aux_Carta_Bot];
          P1_Numero_Cartas -= 1;
          Player_C[Aux_Carta_Bot] = -1;
          Player1_C_Bolean = 1;

          Printa_Placar(Player1_Pontuacao, Player2_Pontuacao, Placar_Rodadas_Resultado, Valor_da_Rodada);
          Printa_Cartas_Bot(Player1_C_Bolean, P1_Numero_Cartas, Player1_C_Atual);
          Printa_Cartas_Player(Player_C[3], Player_C[4], Player_C[5], Player2_C_Atual, Player2_C_Bolean, Player2_Jogadas, Player2_Pontuacao, Player1_Pontuacao);
          my_sleep(1000);
        }
        Resultado_Rodada(Player1_C_Atual, Player2_C_Atual, &Vencedor_Rodada);
        my_sleep(1000);

        if (Vencedor_Rodada == 0)
        {
          Rodada_PontuacaoP1 += 1;
          Rodada_PontuacaoP2 += 1;
          Placar_Rodadas_Resultado[Contador_Rodadas] = 0;
        }
        else if (Vencedor_Rodada == 1)
        {
          Rodada_PontuacaoP1 += 3;
          Rodada_PontuacaoP2 += 0;
          Placar_Rodadas_Resultado[Contador_Rodadas] = 1;
        }
        else if (Vencedor_Rodada == 2)
        {
          Rodada_PontuacaoP1 += 0;
          Rodada_PontuacaoP2 += 3;
          Placar_Rodadas_Resultado[Contador_Rodadas] = 2;
        }
        else
        {
          printf("Erro ao definir vencedor da Rodada");
          my_sleep(5000);
        }
        if(N_Rodada == 1){
          Resultado_R1 = Vencedor_Rodada;
        }

        // CONDICIONAL PARA DEFINIR GANHADOR DO TENTO
        if (Placar_Rodadas_Resultado[0] == 0)
        {
          if (Placar_Rodadas_Resultado[1] == 1)
          {
            Player1_Pontuacao+= Valor_da_Rodada;
            Vencedor_Tento = 1;
          }
          else if (Placar_Rodadas_Resultado[1] == 2)
          {
            Player2_Pontuacao += Valor_da_Rodada;
            Vencedor_Tento = 2;
          }
        }
        else if ((Placar_Rodadas_Resultado[1] == 0) || Placar_Rodadas_Resultado[2] == 0)
        {
          if (Placar_Rodadas_Resultado[0] == 1)
          {
            Player1_Pontuacao += Valor_da_Rodada;
            Vencedor_Tento = 1;
          }
          else if (Placar_Rodadas_Resultado[0] == 2)
          {
            Player2_Pontuacao+= Valor_da_Rodada;
            Vencedor_Tento = 2;
          }
        }
        else if ((Placar_Rodadas_Resultado[0] == 0) && (Placar_Rodadas_Resultado[1] == 0) && (Placar_Rodadas_Resultado[2] == 0))
        {
          Player1_Pontuacao += Valor_da_Rodada;
          Player2_Pontuacao += Valor_da_Rodada;
          Vencedor_Tento = 1;
        }
        else
        {
          if (Contador_Rodadas >= 1)
          {
            if (Rodada_PontuacaoP1 >= 6)
            {
              Player1_Pontuacao += Valor_da_Rodada;
              Vencedor_Tento = 1;
              break;
            }
            else if (Rodada_PontuacaoP2 >= 6)
            {
              Player2_Pontuacao+= Valor_da_Rodada;
              Vencedor_Tento = 2;
              break;
            }
          }
        }
        
        //if(Vencedor_Tento == 1){
        //  Player1_Pontuacao += Valor_da_Rodada; 
        //}
        //if(Vencedor_Tento == 2){
        //  Player2_Pontuacao += Valor_da_Rodada; 
        //}

        system("clear");
        Contador_Rodadas++;
      } while (Vencedor_Tento == 0);
    } while (Player1_Pontuacao < 12 && Player2_Pontuacao < 12);
    // JOGAR NOVAMENTE?
    if (Player1_Pontuacao >= 12){
      Historia_Derrota();
      Ganhou2 = 1; 
    }
    else if(Player2_Pontuacao >= 12){
      Historia_Vitoria();
      Perdeu2 = 1;
    }
    
    AddRank(Ganhou2,Perdeu2,nome_player);
    do
    {
      system("clear");
      printf("==================================================\n");
      printf("       1-Jogar Novamente || 2-Sair\n");
      printf("==================================================\n");
      fflush(stdin);
      scanf("%d", &Jogar_Novamente);
    } while (Jogar_Novamente < 1 && Jogar_Novamente > 2);
  } while (Jogar_Novamente == 1);
}

void Rank()
{
  system("clear");
  FILE *rank;
  char nome[30], top5nome[100][30];
  int derrota, vitoria, top5derrota[100], top5vitoria[100], i = 0, j, k, l;
  rank = fopen("rank.txt","r");
  if(rank == NULL){
  printf("Arquivo de rank nao existe!");
  fclose(rank);
  getchar();
  system("pause");
  return;
  }else{
      while(feof(rank) == 0) {
      fgets(nome, sizeof(nome),rank);
      strcpy(top5nome[i],nome);
      fscanf(rank,"%d ",&vitoria);
      top5vitoria[i] = vitoria;
      fscanf(rank,"%d ",&derrota);
      top5derrota[i] = derrota;
      i++;
    }
  }
  fclose(rank);
  for (int j = 0; j < i ; j++){
     for (int k = j; k < i ; k++){
       if(top5vitoria[k] > top5vitoria[j]){
        l = top5vitoria[j];
        top5vitoria[j] = top5vitoria[k];
        top5vitoria[k] = l;
        l = top5derrota[j];
        top5derrota[j] = top5derrota[k];
        top5derrota[k] = l;
        strcpy(nome,top5nome[j]);
        strcpy(top5nome[j],top5nome[k]);
        strcpy(top5nome[k],nome);
      }
    }
  }
    printf("=====================°------°=====================\n");
    printf("§ § § § § § § § § § §| Rank | § § § § § § § § § § \n");
    printf("=====================°------°=====================\n");
  for(i = 0; i < 5;i++){
    printf("%d°lugar - ",i + 1);
    for(j = 0; top5nome[i][j] != '\0'; j++){
      printf("%c",top5nome[i][j]);
    }
    printf("Vitorias: %d // Derrotas: %d\n",top5vitoria[i],top5derrota[i]);
  }
  printf("=====================°------°=====================\n");
  printf("§ § § § § § § § § § § § § § § §  § § § § § § § § § \n");
  printf("=====================°------°=====================\n");
  printf("Pressione 'ENTER' para voltar ao menu.\n");
  getchar();
  system("pause");
}

// Funcao que Mostra as Regras do Truco
void Regras()
{
  // Variável que representa vai mudar a página do menu de regras
  int Contador_Paginas_Regras;
  // Igualar o contador a 1 para tirar o lixo dele
  Contador_Paginas_Regras = 1;
  // Função que limpa as informações do console
  system("clear");
  // Loop que só termina quando o usuário selecionar a opção de saída (Contador_Paginas_Regras = 4), caso contrário o menu volta a aparecer na página 1
  do
  {
    // If feito para igualar o valor do Contador_Paginas_Regras 1 para que ele volte da página um caso o usuário escreva um valor inválido
    if (Contador_Paginas_Regras != 4 && Contador_Paginas_Regras != 1 && Contador_Paginas_Regras != 2 && Contador_Paginas_Regras != 3)
    {
      Contador_Paginas_Regras = 1;
    }
    // Switch para printar a Página 1 das regras
    switch (Contador_Paginas_Regras)
    {
    case 1:
      printf("=====================°------°=====================\n");
      printf("§ § § § § § § § § § §|Regras| § § § § § § § § § § \n");
      printf("=====================°------°=====================\n");
      printf("- Os 2 jogadores começam com o placar zerado.\n");
      printf("- Cada mao comeca valendo 1 ponto.\n");
      printf("- No decorrer das rodadas os jogadores, na sua vez\n");
      printf("de jogar, podem pedir truco, aumentando o valor da\n");
      printf("mão para 3 pontos.\n");
      printf("- Os adversários podem aceitar, rejeitar ou pedir 6.\n");
      printf("Quando rejeitam, a mao termina e quem pediu truco\n");
      printf("ganha 1 ponto. Caso o adversario peca 6, quem pediu\n");
      printf("truco tem asmesmas possibilidades, aceitar,\n");
      printf("rejeitar, ou aumentar para 9, dessa maneira ate\n");
      printf("o maximo que e 12.\n");
      printf("pagina 1 - 3\n");
      printf("==================================================\n");
      printf("1- Pagina 1 | 2- Pagina 2 | 3- Pagina 3 | 4- Sair\n");
      printf("==================================================\n");
      printf("§ § § § § § § § § § § § § § § § § § § § § § § § § \n");
      printf("==================================================\n");
      break;
    // Switch para printar a Página 2 das regras
    case 2:
      printf("=====================°------°=====================\n");
      printf("§ § § § § § § § § § §|Regras| § § § § § § § § § § \n");
      printf("=====================°------°=====================\n");
      printf("o MÃO DE FERRO:\n");
      printf("- Em caso de empate em 11 a 11, os jogadores dis-\n");
      printf("putam a mão às cegas. As cartas permanecem viradas\n");
      printf("de cabeça para baixo, ninguém pode ver suas próprias\n");
      printf("cartas.\n");
      printf("Quem vencer a mão, ganha o jogo.\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("pagina 2 - 3\n");
      printf("==================================================\n");
      printf("1- Pagina 1 | 2- Pagina 2 | 3- Pagina 3 | 4- Sair\n");
      printf("==================================================\n");
      printf("§ § § § § § § § § § § § § § § § § § § § § § § § § \n");
      printf("==================================================\n");
      break;
    // Switch para printar a Página 3 das regras
    case 3:
      printf("=====================°------°=====================\n");
      printf("§ § § § § § § § § § §|Regras| § § § § § § § § § § \n");
      printf("=====================°------°=====================\n");
      printf("o BARALHO TRUCO MINEIRO:\n");
      printf("- O truco mineiro é jogado com 40 cartas, retirando\n");
      printf("os coringas, 8, 9 e 10. A sequência das cartas,\n");
      printf("independente do naipe, na ordem de + valiosa para\n");
      printf("- valiosa: 3 > 2 > A > k > J > Q > 7 >6 > 5 > 4.\n");
      printf("o MANILHAS:\n");
      printf("- São as cartas com maior valor no Truco. No Truco\n");
      printf("Mineiro, as manilhas sao:\n");
      printf("4 de paus (Zap) > 7 de copas > A de espadas\n");
      printf("(Espadilha) > 7 de ouros.\n");
      printf("\n");
      printf("pagina 3 - 3\n");
      printf("==================================================\n");
      printf("1- Pagina 1 | 2- Pagina 2 | 3- Pagina 3 | 4- Sair\n");
      printf("==================================================\n");
      printf("§ § § § § § § § § § § § § § § § § § § § § § § § § \n");
      printf("==================================================\n");
      break;
    case 4:
      break;
    }
    // scanf que recebe o valor do Contador_Paginas_Regras, caso o usuário queira mudar de página ou voltar para o menu principal do jogo
    scanf("%d", &Contador_Paginas_Regras);
    // Limpa o console, pois caso o usuário deseje apenas mudar de página ele apaga a página printada anteriormente
    system("clear");
  } while (Contador_Paginas_Regras != 4);
}

// Funcao sobre o programa
void Sobre()
{
  system("clear");
  printf("=====================°-----°=====================\n");
  printf("§ § § § § § § § § § §|Sobre| § § § § § § § § § § \n");
  printf("=====================°-----°=====================\n");
  printf("- Nome do programa: Truco Faroeste \n");
  printf("- Versao: 1.2.2\n");
  printf("- Autores: Gustavo Alves Kuabara\n");
  printf("           Victor Gava Senema\n");
  printf("           Willian Henrique Vilela Casa Grandi\n");
  printf("           Fabio Signorini de Freitas\n");
  printf("=================================================\n");
  printf("§ § § § § § § § § § § § § § § § § § § § § § § § §\n");
  printf("=================================================\n");
  printf("Pressione 'ENTER' para voltar ao menu.\n");
  getchar();
  system("pause");
}

// Funcão usada para Receber o nome do Jogador
void Nome_Jogador(char *nome)
{
  system("clear");
  printf("==================================================\n");
  printf("§ § § § § § § § § § § § § § § § § § § § § § § § §  \n");
  printf("==================================================\n");
  printf("\n");
  printf("           Assine seu nome Xerife:\n");
  printf("           .:");
  setbuf(stdin, NULL);
  gets(nome);
  my_sleep(1000);
  system("clear");
  printf("==================================================\n");
  printf("§ § § § § § § § § § § § § § § § § § § § § § § § §  \n");
  printf("==================================================\n");
  printf("\n");
  printf(ANSI_COLOR_GREEN "           Bem vindo Xerife %s!\n" ANSI_COLOR_RESET, nome);
  my_sleep(3000);
  system("clear");
}

// Funcao usada para adicionar delay
void my_sleep(int sleepms)
{
#ifdef WINDOWS_SYSTEM
  Sleep(sleepms);
#else
  usleep(sleepms * 1000);
#endif
}

void Distribui_Cartas(int cartas[6])
{
  int aux;
  for (int i = 0; i < 6; i++)
  {
    // Distribui as cartas aleatoriamente
    cartas[i] = rand() % 39;
    for (int j = i; j >= 0; j--)
    {
      // Confere se alguma carta é repetida
      if (cartas[i] == cartas[j] && i != j)
      {
        do
        {
          cartas[i] = rand() % 39;
        } while (cartas[i] == cartas[j]);
      }
    }
  }
  for (int k = 0; k < 3; k++)
  {
    for (int l = k + 1; l < 3; l++)
    {
      if (cartas[k] > cartas[l])
      {
        aux = cartas[k];
        cartas[k] = cartas[l];
        cartas[l] = aux;
      }
    }
  }
}

void Printa_Naipes(int Carta_Recebida)
{
  switch (Carta_Recebida)
  {
  case -1:
    printf("     ");
    break;
  case 0:
    printf("|4♦ |");
    break;
  case 1:
    printf("|4♠ |");
    break;
  case 2:
    printf("|4♥ |");
    break;
  // 3 até 6: cartas 5
  case 3:
    printf("|5♦ |");
    break;
  case 4:
    printf("|5♠ |");
    break;
  case 5:
    printf("|5♥ |");
    break;
  case 6:
    printf("|5♣ |");
    break;
  // 7 até 10: cartas 6
  case 7:
    printf("|6♦ |");
    break;
  case 8:
    printf("|6♠ |");
    break;
  case 9:
    printf("|6♥ |");
    break;
  case 10:
    printf("|6♣ |");
    break;
  // 11 até 12: cartas 7 (menos ouro e copas)
  case 11:
    printf("|7♠ |");
    break;
  case 12:
    printf("|7♣ |");
    break;
  // 13 até 16: cartas Q
  case 13:
    printf("|Q♦ |");
    break;
  case 14:
    printf("|Q♠ |");
    break;
  case 15:
    printf("|Q♥ |");
    break;
  case 16:
    printf("|Q♣ |");
    break;
  // 17 até 20: cartas J
  case 17:
    printf("|J♦ |");
    break;
  case 18:
    printf("|J♠ |");
    break;
  case 19:
    printf("|J♥ |");
    break;
  case 20:;
    printf("|J♣ |");
    break;
  // 21 até 24: cartas K
  case 21:
    printf("|K♦ |");
    break;
  case 22:
    printf("|K♠ |");
    break;
  case 23:;
    printf("|K♥ |");
    break;
  case 24:
    printf("|K♣ |");
    break;
  // 25 até 27: cartas A(menos espadilha)
  case 25:
    printf("|A♦ |");
    break;
  case 26:
    printf("|A♥ |");
    break;
  case 27:
    printf("|A♣ |");
    break;
  // 28 até 31: cartas 2
  case 28:
    printf("|2♦ |");
    break;
  case 29:
    printf("|2♠ |");
    break;
  case 30:
    printf("|2♥ |");
    break;
  case 31:
    printf("|2♣ |");
    break;
  // 32 até 35: cartas 2
  case 32:
    printf("|3♦ |");
    break;
  case 33:
    printf("|3♠ |");
    break;
  case 34:
    printf("|3♥ |");
    break;
  case 35:
    printf("|3♣ |");
    break;
  // 36 até 39: Manilhas, Ouro, Espada, Copas, Zap
  case 36:
    printf("|7♦ |");
    break;
  case 37:
    printf("|A♠ |");
    break;
  case 38:
    printf("|7♥ |");
    break;
  case 39:
    printf("|4♣ |");
    break;
  }
}

void Printa_Placar(int Pontuacao_P1, int Pontuacao_P2, int Placar_Rodadas_Resultado[3], int Valor)
{
  system("clear");
  printf("        |=============================|\n");
  if(Valor <= 9){
    printf("        |     Valor da rodada: 0%d     |\n", Valor);
  }
  else{
    printf("        |     Valor da rodada: %d     |\n", Valor);
  }
  printf("=================================================\n");
  printf("§ ");
  // Placar do BOT
  for (int i = 0; i < 3; i++)
  {
    if (Placar_Rodadas_Resultado[i] == 0) // empate
    {
      printf(ANSI_COLOR_YELLOW "= " ANSI_COLOR_RESET);
    }
    else if (Placar_Rodadas_Resultado[i] == 1) // Bot ganhou
    {
      printf(ANSI_COLOR_GREEN "¤ " ANSI_COLOR_RESET);
    }
    else if (Placar_Rodadas_Resultado[i] == 2)
    {
      printf(ANSI_COLOR_RED "† " ANSI_COLOR_RESET);
    }
    else
    {
      printf("o ");
    }
  }
  // Rodadas Bot
  printf("| %.2d | Claudiney (Procurado) § § § § § §\n", Pontuacao_P1);
  printf("§ ");

  // Placar do PLAYER
  for (int i = 0; i < 3; i++)
  {
    if (Placar_Rodadas_Resultado[i] == 0) // empate
    {
      printf(ANSI_COLOR_YELLOW "= " ANSI_COLOR_RESET);
    }
    else if (Placar_Rodadas_Resultado[i] == 1) // player perdeu
    {
      printf(ANSI_COLOR_RED "† " ANSI_COLOR_RESET);
    }
    else if (Placar_Rodadas_Resultado[i] == 2) // player ganhou
    {
      printf(ANSI_COLOR_GREEN "¤ " ANSI_COLOR_RESET);
    }
    else
    {
      printf("o ");
    }
  }
  // Rodadas Player
  printf("| %.2d | Xerife § § § § § § § § § § § § § §\n", Pontuacao_P2);
  printf("=================================================\n");
}

void Printa_Cartas_Player(int C1_P2, int C2_P2, int C3_P2, int Carta_Jogada_P2, int Bolean_Carta_P2, int Jogadas_P2, int Pontuacao_P2, int Pontuacao_P1)
{
  printf("\n");
  if (Bolean_Carta_P2 == 0)
  {
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
  }
  if (Bolean_Carta_P2 == 1)
  {
    printf("                      ___\n");
    printf("                     |   |\n");
    printf("                     ");
    Printa_Naipes(Carta_Jogada_P2);
    printf("\n");
    printf("                     |___|\n");
  }
  if (Pontuacao_P2 == 11 && Pontuacao_P1 == 11)
  {
    if (Jogadas_P2 == 0)
    {
      printf("                 ___  ___  ___\n");
      printf("                |~~~||~~~||~~~|\n");
      printf("                |~~~||~~~||~~~|\n");
      printf("                |~~~||~~~||~~~|\n");
      printf("                  1    2    3\n");
    }
    if (Jogadas_P2 == 1)
    {
      printf("                      ___  ___\n");
      printf("                     |~~~||~~~|\n");
      printf("                     |~~~||~~~|\n");
      printf("                     |~~~||~~~|\n");
      printf("                       2    3\n");
    }
    if (Jogadas_P2 == 6)
    {
      printf("                 ___       ___\n");
      printf("                |~~~|     |~~~|\n");
      printf("                |~~~|     |~~~|\n");
      printf("                |~~~|     |~~~|\n");
      printf("                  1         3\n");
    }
    if (Jogadas_P2 == 3)
    {
      printf("                 ___  ___\n");
      printf("                |~~~||~~~|\n");
      printf("                |~~~||~~~|\n");
      printf("                |~~~||~~~|\n");
      printf("                  1    2\n");
    }
    if (Jogadas_P2 == 7)
    {
      printf("                           ___\n");
      printf("                          |~~~|\n");
      printf("                          |~~~|\n");
      printf("                          |~~~|\n");
      printf("                            3\n");
    }
    if (Jogadas_P2 == 4)
    {
      printf("                      ___\n");
      printf("                     |~~~|\n");
      printf("                     |~~~|\n");
      printf("                     |~~~|\n");
      printf("                       2\n");
    }
    if (Jogadas_P2 == 9)
    {
      printf("                 ___\n");
      printf("                |~~~|\n");
      printf("                |~~~|\n");
      printf("                |~~~|\n");
      printf("                  1\n");
    }
    if (Jogadas_P2 == 10)
    {
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
    }
  }
  // Print das Cartas na mao Padrao
  else
  {
    if (Jogadas_P2 == 0)
    {
      printf("                 ___  ___  ___\n");
      printf("                |   ||   ||   |\n");
      printf("                ");
      Printa_Naipes(C1_P2);
      Printa_Naipes(C2_P2);
      Printa_Naipes(C3_P2);
      printf("\n");
      printf("                |___||___||___|\n");
      printf("                  1    2    3\n");
    }
    if (Jogadas_P2 == 1)
    {
      printf("                      ___  ___\n");
      printf("                     |   ||   |\n");
      printf("                ");
      Printa_Naipes(C1_P2);
      Printa_Naipes(C2_P2);
      Printa_Naipes(C3_P2);
      printf("\n");
      printf("                     |___||___|\n");
      printf("                       2    3\n");
    }
    if (Jogadas_P2 == 6)
    {
      printf("                 ___       ___\n");
      printf("                |   |     |   |\n");
      printf("                ");
      Printa_Naipes(C1_P2);
      Printa_Naipes(C2_P2);
      Printa_Naipes(C3_P2);
      printf("\n");
      printf("                |___|     |___|\n");
      printf("                  1         3\n");
    }
    if (Jogadas_P2 == 3)
    {
      printf("                 ___  ___\n");
      printf("                |   ||   |\n");
      printf("                ");
      Printa_Naipes(C1_P2);
      Printa_Naipes(C2_P2);
      Printa_Naipes(C3_P2);
      printf("\n");
      printf("                |___||___|\n");
      printf("                  1    2\n");
    }
    if (Jogadas_P2 == 7)
    {
      printf("                           ___\n");
      printf("                          |   |\n");
      printf("                ");
      Printa_Naipes(C1_P2);
      Printa_Naipes(C2_P2);
      Printa_Naipes(C3_P2);
      printf("\n");
      printf("                          |___|\n");
      printf("                            3\n");
    }
    if (Jogadas_P2 == 4)
    {
      printf("                      ___\n");
      printf("                     |   |\n");
      printf("                ");
      Printa_Naipes(C1_P2);
      Printa_Naipes(C2_P2);
      Printa_Naipes(C3_P2);
      printf("\n");
      printf("                     |___|\n");
      printf("                       2\n");
    }
    if (Jogadas_P2 == 9)
    {
      printf("                 ___\n");
      printf("                |   |\n");
      printf("                ");
      Printa_Naipes(C1_P2);
      Printa_Naipes(C2_P2);
      Printa_Naipes(C3_P2);
      printf("\n");
      printf("                |___|\n");
      printf("                  1\n");
    }
    if (Jogadas_P2 == 10)
    {
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
      printf("\n");
    }
  }
  printf("=================================================\n");
  printf("§ § § § § § § § § § § § § § § § § § § § § § § § § \n");
  printf("§ § § § § § § § § § § § § § § § § § § § § § § § § \n");
  printf("=================================================\n");
}

void Printa_Cartas_Bot(int Bolean_Carta_P1, int Numero_Cartas_P1, int Carta_Jogada_P1)
{
  // Print Cartas Player 1 com 3 Cartas
  if (Numero_Cartas_P1 == 3)
  {
    printf("                 ___  ___  ___\n");
    printf("                |~~~||~~~||~~~|\n");
    printf("                |~~~||~~~||~~~|\n");
    printf("                |~~~||~~~||~~~|\n");
  }
  // Print Cartas Player 2 com 0 Cartas
  if (Numero_Cartas_P1 == 2)
  {
    printf("                 ___  ___\n");
    printf("                |~~~||~~~|\n");
    printf("                |~~~||~~~|\n");
    printf("                |~~~||~~~|\n");
  }
  // Print Cartas Player 1 com 1 Carta
  if (Numero_Cartas_P1 == 1)
  {
    printf("                 ___\n");
    printf("                |~~~|\n");
    printf("                |~~~|\n");
    printf("                |~~~|\n");
  }
  // Print Cartas Player 1 com 0 Cartas
  if (Numero_Cartas_P1 == 0)
  {
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
  }
  // If que confere se a carta foi jogada pelo bot ou não e printa em caso afirmativo
  if (Bolean_Carta_P1 == 1)
  {
    printf("                      ___\n");
    printf("                     |   |\n");
    printf("                     ");
    Printa_Naipes(Carta_Jogada_P1);
    printf("\n");
    printf("                     |___|\n");
  }
  if (Bolean_Carta_P1 == 0)
  {
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
  }
  printf("\n");
  printf("                       x\n");
}

void Pedir_Truco_Tipo_1(int *Valor_Rodada_Tipo1, int *Check_Player_Plus_Tento_Tipo1, int *Ganhador_Tento_Tipo1, int *Tipo_Usado_Tipo1)
{
  int resposta;
  if (Valor_Rodada_Tipo1 == 1 && Check_Player_Plus_Tento_Tipo1 == 0)
  {
    // Se Bot Pedir Truco
    if (Bot_IA_Truco == 1)
    {
      Check_Player_Plus_Tento_Tipo1 = 2;
      Tipo_Usado_Tipo1 = 1;
      // Player Aceita truco
      do
      {
        printf("4- Aceitar Truco   5- Recusar Truco\n");
        scanf("%d", &resposta);
      } while (resposta != 4 && resposta != 5 && resposta != 6);
      if (resposta == 1)
      {
        Valor_Rodada_Tipo1 = 3;
      }
      // Player Recusa Truco
      if (resposta == 2)
      {
        Valor_Rodada_Tipo1 = 1;
        Ganhador_Tento_Tipo1 = 1;
      }
      // Player Pede 6
      if (resposta == 1)
      {
        do
        {
          printf("6- Pedir SEIS!! 7- Passar\n");
          scanf("%d", &resposta);
          if (resposta == 6)
          {
            Check_Player_Plus_Tento_Tipo1 = 2;
            Valor_Rodada_Tipo1 = 6;
          }
        } while (resposta != 6 && resposta != 7);
      }
    }
  }

  if (Valor_Rodada_Tipo1 == 6 && Check_Player_Plus_Tento_Tipo1 == 2)
  {
    // Bot Aceita SEIS
    if (Bot_IA_Truco == 1)
    {
      Valor_Rodada_Tipo1 = 6;
    }
    // Bot Recusa 6
    if (Bot_IA_Truco == 2)
    {
      Valor_Rodada_Tipo1 = 3;
      Ganhador_Tento_Tipo1 = 2;
    }
    // Bot Pede 9
    if (Bot_IA_Truco == 3)
    {
      Check_Player_Plus_Tento_Tipo1 = 1;
      Valor_Rodada_Tipo1 = 9;
    }
  }

  if (Valor_Rodada_Tipo1 == 9 && Check_Player_Plus_Tento_Tipo1 == 1)
  {
    // Player Aceita 6
    printf("4- Aceitar Truco   5- Recusar Truco\n");
    scanf("%d", &resposta);
    if (resposta == 4)
    {
      Valor_Rodada_Tipo1 = 6;
    }
    // Player Recusa 6
    if (Bot_IA_Truco == 5)
    {
      Valor_Rodada_Tipo1 = 3;
      Ganhador_Tento_Tipo1 = 1;
    }
    // Player Pede 12
    if (resposta == 4)
    {
      do
      {
        printf("6- Pedir NOVE!! 7- Passar\n");
        scanf("%d", &resposta);
        if (resposta == 6)
        {
          Check_Player_Plus_Tento_Tipo1 = 2;
          Valor_Rodada_Tipo1 = 12;
        }
      } while (resposta != 6 && resposta != 7);
    }
  }

  if (Valor_Rodada_Tipo1 == 12 && Check_Player_Plus_Tento_Tipo1 == 1)
  {
    // Bot Aceita truco
    if (Bot_IA_Truco == 1)
    {
      Valor_Rodada_Tipo1 = 12;
    }
    // Bot Recusa Truco
    if (Bot_IA_Truco == 2)
    {
      Valor_Rodada_Tipo1 = 9;
      Ganhador_Tento_Tipo1 = 2;
    }
  }
}

void Pedir_Truco_Tipo_2(int *Valor_Rodada_Tipo2, int *Check_Player_Plus_Tento_Tipo2, int *Ganhador_Tento_Tipo2, int *Tipo_Usado_Tipo2)
{
  int resposta;
  if (Valor_Rodada_Tipo2 == 1 && Check_Player_Plus_Tento_Tipo2 == 0)
  {
    do
    {
      printf("4- Pedir Truco   5- Recusar Truco\n");
      scanf("%d", &resposta);
    } while (resposta != 4 && resposta != 5);
    // Se Player Pedir Truco
    if (resposta == 1)
    {
      Check_Player_Plus_Tento_Tipo2 = 2;
      Tipo_Usado_Tipo2 = 2;
      // Bot Aceita truco
      if (Bot_IA_Truco == 1)
      {
        Valor_Rodada_Tipo2 = 3;
      }
      // Bot Recusa Truco
      if (Bot_IA_Truco == 2)
      {
        Valor_Rodada_Tipo2 = 1;
        Ganhador_Tento_Tipo2 = 2;
      }
      // Bot Pede 6
      if (Bot_IA_Truco == 3)
      {
        Check_Player_Plus_Tento_Tipo2 = 1;
        Valor_Rodada_Tipo2 = 6;
      }
    }
  }

  if (Valor_Rodada_Tipo2 == 6 && Check_Player_Plus_Tento_Tipo2 == 2)
  {
    do
    {
      printf("4- Aceitar   5- Recusar seis\n");
      scanf("%d", &resposta);
    } while (resposta != 4 && resposta != 5);
    // Player Aceita SEIS
    if (resposta == 4)
    {
      Valor_Rodada_Tipo2 = 6;
    }
    // Player Recusa 6
    if (resposta == 5)
    {
      Valor_Rodada_Tipo2 = 3;
      Ganhador_Tento_Tipo2 = 1;
    }
    // Player Pede 9
    if (Bot_IA_Truco == 4)
    {
      do
      {
        printf("6- Pedir Nove!   7- Passar\n");
        scanf("%d", &resposta);
      } while (resposta != 6 && resposta != 7);
      if (resposta == 6)
      {
        Check_Player_Plus_Tento_Tipo2 = 2;
        Valor_Rodada_Tipo2 = 9;
      }
    }
  }

  if (Valor_Rodada_Tipo2 == 9 && Check_Player_Plus_Tento_Tipo2 == 1)
  {
    // Bot Aceita 9
    if (Bot_IA_Truco == 1)
    {
      Valor_Rodada_Tipo2 = 9;
    }
    // Bot Recusa 9
    if (Bot_IA_Truco == 2)
    {
      Valor_Rodada_Tipo2 = 6;
      Ganhador_Tento_Tipo2 = 2;
    }
    // Bot Pede 12
    if (Bot_IA_Truco == 3)
    {
      Check_Player_Plus_Tento_Tipo2 = 1;
      Valor_Rodada_Tipo2 = 12;
    }
  }

  if (Valor_Rodada_Tipo2 == 12 && Check_Player_Plus_Tento_Tipo2 == 1)
  {
    do
    {
      printf("4- Aceitar   5- Recusar Doze\n");
      scanf("%d", &resposta);
    } while (resposta != 4 && resposta != 5);
    // Player Aceita truco
    if (resposta == 4)
    {
      Valor_Rodada_Tipo2 = 12;
    }
    // Player Recusa Truco
    if (Bot_IA_Truco == 5)
    {
      Valor_Rodada_Tipo2 = 9;
      Ganhador_Tento_Tipo2 = 1;
    }
  }
}

int Resultado_Rodada(int Carta_Jogada_P1, int Carta_Jogada_P2, int *Vencedor_Rodada)
{

  int Pontuacao_P1 = Forca_Carta(Carta_Jogada_P1);
  int Pontuacao_P2 = Forca_Carta(Carta_Jogada_P2);

  if (Pontuacao_P1 == Pontuacao_P2)
  {
    *Vencedor_Rodada = 0;
    printf("Empate! \n");
    Pontuacao_P1 += 1;
    Pontuacao_P2 += 1;
  }
  if (Pontuacao_P1 > Pontuacao_P2)
  {
    *Vencedor_Rodada = 1;
    printf("Claudiney disparou mais rapido!\n");
    Pontuacao_P1 += 4;
  }
  if (Pontuacao_P1 < Pontuacao_P2)
  {
    *Vencedor_Rodada = 2;
    printf("Boa Xerife!\n");
    Pontuacao_P2 += 4;
  }
}

int Forca_Carta(int Valor_Carta)
{
  if (Valor_Carta >= 0 && Valor_Carta <= 2)
    return 0;
  else if (Valor_Carta >= 3 && Valor_Carta <= 6)
    return 1;
  else if (Valor_Carta >= 7 && Valor_Carta <= 10)
    return 2;
  else if (Valor_Carta >= 11 && Valor_Carta <= 12)
    return 3;
  else if (Valor_Carta >= 13 && Valor_Carta <= 16)
    return 4;
  else if (Valor_Carta >= 17 && Valor_Carta <= 20)
    return 5;
  else if (Valor_Carta >= 21 && Valor_Carta <= 24)
    return 6;
  else if (Valor_Carta >= 25 && Valor_Carta <= 27)
    return 7;
  else if (Valor_Carta >= 28 && Valor_Carta <= 31)
    return 8;
  else if (Valor_Carta >= 32 && Valor_Carta <= 35)
    return 9;
  else if (Valor_Carta == 36)
    return 10;
  else if (Valor_Carta == 37)
    return 11;
  else if (Valor_Carta == 38)
    return 12;
  else if (Valor_Carta == 39)
    return 13;
  return -1;
}

int Bot_IA_Truco()
{
  // 1 Pede/Aceita Truco
  return 1;
  // 2 Recusa truco
  // 3 Aumenta o valor do tento
}

void Historia_Derrota()
{
    char c = 92;
    int i, j;
    char Fala_1[58] = "Parece que essa cidade eh pequena demais para nos, XERIFE!";
    char Fala_2[59] = "Voce Perdeu, Claudiney continuara a comandar a cidade 69!!";
    for(i = 0; Fala_1[i] != '\0'; i++){
        if(i != 58){
            if(i % 2 != 0){
                system("clear");
                printf("  ___\n");
                printf(" /___%c\n", c);
                printf("c--o>o|\n");
                printf(" %c__-/\n", c);
                printf(" / /%c%c\n", c, c);
                printf(" |/  ||  ");
            }
            if(i % 2 == 0){
                system("clear");
                printf("  ___\n");
                printf(" /___%c\n", c);
                printf("c--o>o|\n");
                printf(" %c__o/\n", c);
                printf(" / /%c%c\n", c, c);
                printf(" |/  ||  ");
            }
        }
        else{
            system("clear");
            printf("  ___\n");
            printf(" /___%c\n", c);
            printf("c--o>o|\n");
            printf(" %c__-/\n", c);
            printf(" / /%c%c  ¶==\n", c, c);
            printf(" |/  ||// ");
        }
        for(j = 0; j != i; j++){
            printf("%c", Fala_1[j]);
            fflush(stdout);
        }
        my_sleep(70);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    for(i = 0; Fala_2[i] != '\0'; i++){
        printf("%c", Fala_2[i]);
        fflush(stdout);
        my_sleep(50);
    }
    my_sleep(1000);
}

void Historia_Vitoria()
{
    char c = 92;
    int i, j;
    char Fala_1[63] = "Parece que essa cidade eh pequena demais para nos, XERIFE!";
    char Fala_2[55] = "Parabens Xerife, voce encontrou e derrotou Claudiney!!";
    char Fala_3[71] = "Voce conseguiu!! Agora que Claudiney voltou para a cidade de Ponteiros";
    char Fala_4[72] = "A cidade 69 esta em boas maos com Dantas voltando a assumir a lideranca";
    for(i = 0; Fala_1[i] != '\0'; i++){
        if(i % 2 != 0){
            system("clear");
            printf("  ___\n");
            printf(" /___%c\n", c);
            printf("c--o>o|\n");
            printf(" %c__-/\n", c);
            printf(" / /%c%c\n", c, c);
            printf(" |/  ||");
        }
        if(i % 2 == 0){
            system("clear");
            printf("  ___\n");
            printf(" /___%c\n", c);
            printf("c--o>o|\n");
            printf(" %c__o/\n", c);
            printf(" / /%c%c\n", c, c);
            printf(" |/  ||");
        }
        for(j = 0; j != i; j++){
            printf("%c", Fala_1[j]);
            fflush(stdout);
        }
        my_sleep(70);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    for(i = 0; Fala_2[i] != '\0'; i++){
        printf("%c", Fala_2[i]);
        fflush(stdout);
        my_sleep(50);
    }
    printf("\n");
    printf("\n");
    for(i = 0; Fala_3[i] != '\0'; i++){
        printf("%c", Fala_3[i]);
        fflush(stdout);
        my_sleep(50);
    }
    printf("\n");
    printf("\n");
    for(i = 0; Fala_4[i] != '\0'; i++){
        printf("%c", Fala_4[i]);
        fflush(stdout);
        my_sleep(50);
    }
    my_sleep(1000);
}

int Forca_Cartas_Bot(int Carta1, int Carta2, int Carta3)
{
    int Carta_Bot[3];
    Carta_Bot[0] = Carta1;
    Carta_Bot[1] = Carta2;
    Carta_Bot[2] = Carta3;
    int Forca_Mao_Bot = 0;
    int i;
    for(i = 0; i < 3; i ++){
        if(Carta_Bot[i] >= 0 && Carta_Bot[i] <= 2){
            Forca_Mao_Bot += 0;
        }
        if(Carta_Bot[i] >= 3 && Carta_Bot[i] <= 6){
            Forca_Mao_Bot += 1;
        }
        if(Carta_Bot[i] >= 7 && Carta_Bot[i] <= 10){
            Forca_Mao_Bot += 2;
        }
        if(Carta_Bot[i] >= 11 && Carta_Bot[i] <= 12){
            Forca_Mao_Bot += 3;
        }
        if(Carta_Bot[i] >= 13 && Carta_Bot[i] <= 16){
            Forca_Mao_Bot += 4;
        }
        if(Carta_Bot[i] >= 17 && Carta_Bot[i] <= 20){
            Forca_Mao_Bot += 5;
        }
        if(Carta_Bot[i] >= 21 && Carta_Bot[i] <= 24){
            Forca_Mao_Bot += 6;
        }
        if(Carta_Bot[i] >= 25 && Carta_Bot[i] <= 27){
            Forca_Mao_Bot += 7;
        }
        if(Carta_Bot[i] >= 28 && Carta_Bot[i] <= 31){
            Forca_Mao_Bot += 8;
        }
        if(Carta_Bot[i] >= 32 && Carta_Bot[i] <= 35){
            Forca_Mao_Bot += 9;
        }
        if(Carta_Bot[i] == 36){
            Forca_Mao_Bot += 10;
        }
        if(Carta_Bot[i] == 37){
            Forca_Mao_Bot += 11;
        }
        if(Carta_Bot[i] == 38){
            Forca_Mao_Bot += 12;
        }
        if(Carta_Bot[i] == 39){
            Forca_Mao_Bot += 13;
        }
    }
    return Forca_Mao_Bot;
}

int Bot_IA(int R1, int Carta_jogadaP2, int media, int *Player_K, int R_Atual, int carta_fraca, int carta_media, int carta_forte, int carta_jogada1, int Carta_jogada2, int Bot_Joga_Primeiro, int Pontuacao1, int Pontuacao2)
{
   //contador 
   int i, j;
   //checagem de cartas
   int Check_play = 0;
   //Decisão de jogada do Jogador 2
   //int Carta_JogadaP2;
   //Varialvel que da o retorno se deve jogar carta Player_K[0] ou Player_K[1] ou Player_K[2]
   //Player_K[0] = 1°carta; Player_K[1] = 2°carta, Player_K[2] = 3°carta
   int Carta_JogadaP1 = - 1;
   //R1 = 0 ,Empate
   //R1 = 1 ,Vitoria
   //R1 = 2 ,Derrota
   //R1 = -1 Ainda nÃ£o tem resultado
   //Bot joga_Primeiro == 1 O bot começa a rodada
   //Bot Joga_Primeiro == 0 O bot é o segundo a jogar na rodada
   if(Pontuacao1 != 11 || Pontuacao2 != 11){
    if(Bot_Joga_Primeiro == 1){
        if(media >= 0 && media <= 8){
            if(R_Atual == 1){
                Carta_JogadaP1 = 2;
                return Carta_JogadaP1;
            }
            if(R_Atual == 2){
                if(R1 == 0){
                    if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                    
                }
                if(R1 == 1){
                    if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 2){
                    if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                    }else if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                    }else if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                    }
                    return Carta_JogadaP1;
                }
            }
            if(R_Atual == 3){
                if(R1 == 0){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 1){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                    }
                    return Carta_JogadaP1;
                    return Carta_JogadaP1;
                }
                if(R1 == 2){
                    if(carta_jogada1 != 0 && Carta_jogada2 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }
                    return Carta_JogadaP1;
                }
            }
        }
        if(media >= 9 && media <= 18){
            if(R_Atual == 1){
                Carta_JogadaP1 = 2;
                return Carta_JogadaP1;
            }
            if(R_Atual == 2){
                if(R1 == 0){
                    if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 1){
                    if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }
                   
                }
                if(R1 == 2){
                    if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                    return Carta_JogadaP1;
                }
            }
            if(R_Atual == 3){
                if(R1 == 0){
                    if(carta_jogada1 != 0 && Carta_jogada2 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 1){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 2){
                    if(carta_jogada1 != 2 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
            }
        }
        if(media >= 19 && media <= 23){
            if(R_Atual == 1){
                Carta_JogadaP1 = 2;
                return Carta_JogadaP1;
            }
            if(R_Atual == 2){
                if(R1 == 0){
                    if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 1){
                    if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 2){
                    if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }
                }
            }
            if(R_Atual == 3){
                if(R1 == 0){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 1){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 2){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
            }
        }
        if(media >= 24 && media <= 27){
            if(R_Atual == 1){
                Carta_JogadaP1 = 2;
                return Carta_JogadaP1;
            }
            if(R_Atual == 2){
                if(R1 == 0){
                    if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 1){
                    if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 2){
                    if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
            }
            if(R_Atual == 3){
                if(R1 == 0){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 1){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 2){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
            }
        }
        if(media >= 28 && media <= 31){
            if(R_Atual == 1){
                Carta_JogadaP1 = 1;
                return Carta_JogadaP1;
            }
            if(R_Atual == 2){
                if(R1 == 0){
                    if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 1){
                    if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 2){
                    if(carta_jogada1 != 2){
                      Carta_JogadaP1 = 2;
                    }else if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                    }else{
                      Carta_JogadaP1 = 0;
                    }
                    return Carta_JogadaP1;
                }
            }
            if(R_Atual == 3){
                if(R1 == 0){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                    }else{
                      Carta_JogadaP1 = 0;
                    }
                    return Carta_JogadaP1;
                }
                if(R1 == 1){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
                if(R1 == 2){
                    if(carta_jogada1 != 1 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }
                }
            }
        }
        if(media >= 32){
            if(R_Atual == 1){
                Carta_JogadaP1 = 0;
                return Carta_JogadaP1;
            }
            if(R_Atual == 2){
                    if(carta_jogada1 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 0){
                      Carta_JogadaP1 = 0;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }
            }
            if(R_Atual == 3){
                if(carta_jogada1 != 1 && Carta_jogada2 != 2){
                      Carta_JogadaP1 = 2;
                      return Carta_JogadaP1;
                    }else if(carta_jogada1 != 2 && Carta_jogada2 != 1){
                      Carta_JogadaP1 = 1;
                      return Carta_JogadaP1;
                    }else{
                      Carta_JogadaP1 = 0;
                    }
                return Carta_JogadaP1;
            }
        }
      }
    }
    if (Bot_Joga_Primeiro == 0)
    {
        if(R_Atual == 1){
            for(i = 0; i < 3; i++){
                if(Player_K[i] >= carta_jogada1){
                    Carta_JogadaP1 = i;
                    Check_play = 1;
                    return Carta_JogadaP1;
                }
                    
            }
            if(Check_play == 0){
                Carta_JogadaP1 = 0;
                return Carta_JogadaP1;
            }
        }
        if(R_Atual == 2){
            for(i = 0; i < 3; i++){
                if(Player_K[i] >= Carta_jogadaP2 && Player_K[i] != carta_jogada1){
                        Carta_JogadaP1 = i;
                        Check_play = 1;
                        return Carta_JogadaP1;
                    }
                    
            }
            if(Check_play == 0){
                if((carta_jogada1 != carta_fraca)){
                    Carta_JogadaP1 = 0;
                    return Carta_JogadaP1;
                }else if(carta_jogada1 != carta_media){
                    Carta_JogadaP1 = 1;
                    return Carta_JogadaP1;
                }else if(carta_jogada1 != carta_forte){
                    Carta_JogadaP1 = 2;
                    return Carta_JogadaP1;
                }
            }
        }
        if(R_Atual == 3){
            for(i = 0; i < 3; i++){
                if(Player_K[i] >= Carta_jogadaP2 && i != carta_jogada1 && i != Carta_jogada2){
                    Carta_JogadaP1 = i;
                    Check_play = 1;
                    return Carta_JogadaP1;
                }
                
            }
            if(Check_play == 0){
                if(Player_K[carta_jogada1] != carta_fraca && Player_K[Carta_jogada2] != carta_fraca){
                    Carta_JogadaP1 = 0;
                    return Carta_JogadaP1;
                }else if(Player_K[carta_jogada1] != carta_media && Player_K[Carta_jogada2] != carta_media){
                    Carta_JogadaP1 = 1;
                    return Carta_JogadaP1;
                }else if(Player_K[carta_jogada1] != carta_forte && Player_K[Carta_jogada2] != carta_forte){
                    Carta_JogadaP1 = 2;
                    return Carta_JogadaP1;
                }
            }
        }
    }   
  }else{
    if(R_Atual == 1){
      Carta_JogadaP1 = rand() % 2;
      return Carta_JogadaP1;
    }else if(R_Atual == 2){
      do{
         Carta_JogadaP1 = rand() % 2;
      }while(Carta_JogadaP1 == carta_jogada1);
      return Carta_JogadaP1;
    }else if(R_Atual == 2){
      do{
         Carta_JogadaP1 = rand() % 2;
      }while(Carta_JogadaP1 == carta_jogada1 && Carta_JogadaP1 == Carta_jogada2);
      return Carta_JogadaP1;
    }
  }
}

void AddRank(int Ganhou,int Perdeu,char *nome)
{
    FILE *rank;
    int i, verifica, x, y;
    char nomes_no_arquivo[30];
    
    rank = fopen("rank.txt","w");
    rewind(rank);
    while(fscanf(rank,"%s",nomes_no_arquivo) != EOF){
        verifica = 0;
        for(i = 0; nome[i] != '\0'; i++){
            if(nome[i] != nomes_no_arquivo[i]){
                verifica = 1;
            }
        }
        if(verifica == 0){
            break;
            fscanf(rank,"%d\n%d",&x,&y);
            x += Ganhou;
            y += Perdeu;
        }
    }
    if(verifica != 0){
        fseek(rank,0,SEEK_END);
        fputs(nome,rank);
        fscanf(rank,"%d %d",&x,&y);
        x += Ganhou;
        y += Perdeu;
        fprintf(rank,"\n%d\n%d",x,y);
    }
    fclose(rank);
}