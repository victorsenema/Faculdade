typedef struct Estacionamento estacionamento;
estacionamento **criarEstacionamento(int nlinhas, int ncolunas);
void liberaEstacionamento(estacionamento **E, int ncolunas);
estacionamento **criarNumVaga(int nlinhas, int ncolunas, estacionamento **E);
void mudaCorVaga(int TipoVaga, int StatusVaga);
void organizaNumero(int *n1, int *n2);
int contaCasasNumero(int n);
void modelagemEstacionamento(estacionamento **E, int nlinha1, int nlinha2,
                             int ncoluna1, int ncoluna2, int nlinhaMAX,
                             int ncolunaMAX, int operador);
void estabeleceNumVaga(estacionamento **E, int nlinhas, int ncolunas);
void printEstacionamento(estacionamento **E, int nlinhas, int ncolunas);
void printVagaExistente(int Quantidade_Casas, int numVaga);
void printVagaInexistente(int Quantidade_Casas);
void printVagaManutencao(int Quantidade_Casas);
void printNumColunas(int Quantidade_Casas, int ncolunas);
void estacionamentoLegenda();
void consertaPosicoesInvalidas(int nlinhas, int ncolunas, int *nlinha1,
                               int *nlinha2, int *ncoluna1, int *ncoluna2);
void estacionamentoInfo(estacionamento **E, int ncolunas, int nlinhas, int *nv,
                        int *nvd, int *nvi, int *nvv);
int buscaVagaLivreDeficiente(estacionamento **E, int nlinhas, int ncolunas);
int buscaVagaLivreIdoso(estacionamento **E, int nlinhas, int ncolunas);
int buscaVagaLivreVip(estacionamento **E, int nlinhas, int ncolunas);
int buscaVagaLivreComum(estacionamento **E, int nlinhas, int ncolunas);
int buscaVagaLivre(estacionamento **E, int nlinhas, int ncolunas);
estacionamento *procuraV(estacionamento **E, int nlinhas, int ncolunas, int p);
void alteraStatus(estacionamento **E, int nlinhas, int ncolunas, int numvaga, int status);
void InfoVaga(estacionamento **E, int nlinhas, int ncolunas, int p, int *num, int *tip, int *stat);

