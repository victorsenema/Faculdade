package Dados_Graduacao;
import Pessoa.Pessoa;

import java.util.ArrayList;

public class Professor extends Pessoa implements MostraClasse{
    private int inicioDoContrato;
    private String departamentoVinculado;

    public String imprimeDados() {
        return ("Nome: " + getNome() + " | CPF: " + getCpf() + " | Data de Nascimento: " + getDataNascimento() + " | Inicio Contrato: " + inicioDoContrato + " | DepartamentoVinculado: " + departamentoVinculado);
    }
    
    public Professor(String cpf, String nome, String dataNascimento, int inicioDoContrato, String departamentoVinculado) {
        super(cpf, nome, dataNascimento);
        this.inicioDoContrato = inicioDoContrato;
        this.departamentoVinculado = departamentoVinculado;
    }

    public int getInicioDoContrato() {
        return inicioDoContrato;
    }

    public void setInicioDoContrato(int inicioDoContrato) {
        this.inicioDoContrato = inicioDoContrato;
    }

    public String getDepartamentoVinculado() {
        return departamentoVinculado;
    }

    public void setDepartamentoVinculado(String departamentoVinculado) {
        this.departamentoVinculado = departamentoVinculado;
    }

    public void mostra(){
    	System.out.println(toStringInfo());
    }

    public String toStringInfo() {
        return "Nome: " + getNome() + " | Departamento Vinculado: " + getDepartamentoVinculado() + "\n";
    }

    public Professor procuraProfessor(ArrayList<Professor> professores, String cpf) {
        for (Professor professor : professores) {
            if (professor.getCpf().equals(cpf))
                return professor;
        }
        return null;
    }
}