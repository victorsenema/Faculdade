package Dados_Graduacao;
import Pessoa.Pessoa;

import java.util.ArrayList;
import java.util.List;

public class Estudante extends Pessoa implements MostraClasse{
	private float cra;

    public String imprimeDados() {
        return "Nome: " + getNome() + " | CPF: " + getCpf() + " | Data de Nascimento: " + getDataNascimento() + " | CRA: " + cra;
    }

    public Estudante(String cpf, String nome, String dataNascimento, float cra){
        super(cpf, nome, dataNascimento);
        this.cra = cra;
    }

    public float getCra() {
        return cra;
    }

    public void setCra(float cra) {
        this.cra = cra;
    }

    public void mostra(){
        System.out.println(toStringInfo());
    }

    public String toStringInfo(){

        return "Nome: " + getNome() + " | CPF: " + getCpf();
    }
}
