package Dados_Graduacao;

public class PosGraduando extends Estudante{
    private String temaDePesquisa;

    public String imprimeDados() {
        return super.imprimeDados() + " | Tema da Pesquisa: " + temaDePesquisa;
    }
    
    public PosGraduando(String cpf, String nome,String dataNascimento, float cra, String temaDePesquisa){
        super(cpf,nome,dataNascimento,cra);
        this.temaDePesquisa = temaDePesquisa;
    }

    public String getTemaDePesquisa() {
        return temaDePesquisa;
    }

    public void setTemaDePesquisa(String temaDePesquisa) {
        this.temaDePesquisa = temaDePesquisa;
    }
}