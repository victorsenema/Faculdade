package Dados_Graduacao;

import java.util.ArrayList;
import java.util.List;

public abstract class Busca {

    public static Estudante procuraEstudante(List<Estudante> estudantes, String cpf){
        for(Estudante estudante : estudantes){
            if(estudante.getCpf().equals(cpf)){
                return estudante;
            }
        }
        return null;
    }

    public static Professor procuraProfessor(List<Professor> professores, String cpf) {
        for (Professor professor : professores) {
            if (professor.getCpf().equals(cpf))
                return professor;
        }
        return null;
    }

    public static Disciplina procuraDisciplina(List<Disciplina> disciplinas, String codigo) {
        for (Disciplina disciplina : disciplinas) {
            if (disciplina.getCodigo().equals(codigo))
                return disciplina;
        }
        return null;
    }
}