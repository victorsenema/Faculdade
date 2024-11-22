package Dados_Graduacao;

import java.util.ArrayList;
import java.util.List;



public class Disciplina implements MostraClasse{
    private String codigo;
    private String nome;
    private int cargaHoraria;
    
    public String toString() {
        return "Nome Disciplina: " + nome + " | Código: " + codigo + " | Carga Horária: " + cargaHoraria;
    }
    
    public Disciplina(String codigo, String nome, int cargaHoraria) {
        this.codigo = codigo;
        this.nome = nome;
        this.cargaHoraria = cargaHoraria;
    }

    public void mostra(){
    	System.out.println(toStringInfo());
    }

    public String toStringInfo() {
        return "Nome Disciplina: " + nome + " | Codigo: " + codigo + "\n";
    }

    public String getCodigo() {
        return codigo;
    }

    public void setCodigo(String codigo) {
        this.codigo = codigo;
    }

    public String getNomeDisciplina() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getCargaHoraria() {
        return cargaHoraria;
    }

    public void setCargaHoraria(int cargaHoraria) {
        this.cargaHoraria = cargaHoraria;
    }

    public Disciplina procuraDisciplina(ArrayList<Disciplina> disciplinas, String codigo) {
        for (Disciplina disciplina : disciplinas) {
            if (disciplina.getCodigo().equals(codigo))
                return disciplina;
        }
        return null;
    }
}
