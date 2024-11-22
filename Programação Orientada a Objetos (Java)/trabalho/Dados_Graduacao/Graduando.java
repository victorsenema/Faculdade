package Dados_Graduacao;

public class Graduando extends Estudante{
	private boolean estagioSupervisionado;
    
    public String imprimeDados() {
        return super.imprimeDados() + " | Estagio supervisionado: " + estagioSupervisionado;
    }
    
	public Graduando(String cpf, String nome, String dataNascimento, float cra, boolean estagioSupervisionado) {
        super(cpf, nome, dataNascimento, cra);
        this.estagioSupervisionado = estagioSupervisionado;
    }

    public boolean getEstagioSupervisionado() {
        return estagioSupervisionado;
    }

    public void setEstagioSupervisionado(boolean estagioSupervisionado) {
        this.estagioSupervisionado = estagioSupervisionado;
    }
}
