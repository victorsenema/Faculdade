package Dados_Graduacao;
import java.util.ArrayList;
import java.util.List;

public class Turma{
    private int ano;
    private int semestre;
    private Disciplina disciplina;
    private List <Estudante> estudantes;
    private Professor professor;

    public void mostraTurma() {
        System.out.println("-----------------------------------------------------------------------------------------------------------------------------------------");
        System.out.println("Ano: " + ano + " | Semestre: " + semestre + " | Disciplina: " + disciplina.toString() + " | Professor: " + professor.getNome());
        for (Estudante est: estudantes) {
            if(est == null) break;
            est.mostra();
        }
    }

    public Turma(Disciplina disciplina, int ano, int semestre, Professor professor, List <Estudante> estudantes) {
        this.estudantes = new ArrayList<>(estudantes);
        this.disciplina = new Disciplina(disciplina.getCodigo(), disciplina.getNomeDisciplina(), disciplina.getCargaHoraria());
        this.ano = ano;
        this.semestre = semestre;
        this.professor = professor;
    }

    public Disciplina getDisciplina() {
        return disciplina;
    }

    public void setDisciplina(Disciplina disciplina) {
        this.disciplina = disciplina;
    }

    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public int getSemestre() {
        return semestre;
    }

    public void setSemestre(int semestre) {
        this.semestre = semestre;
    }

    public List<Estudante> getEstudantes() {
        return estudantes;
    }

    public void setEstudantes(List<Estudante> estudantes) {
        this.estudantes = estudantes;
    }

    public Professor getProfessor() {
        return professor;
    }

    public void setProfessor(Professor professor) {
        this.professor = professor;
    }
}