package Arquivos;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import Dados_Graduacao.*;

public abstract class GerenciadorArquivos {
    //De estudantes está certo
	public static List<Estudante> leituraEstudantes(){
        List<Estudante> estudantes = new ArrayList<>();
        try {
            Graduando auxG1;
            PosGraduando auxG2;
            FileReader ent = new FileReader("Arquivos/Alunos.txt");
            BufferedReader br = new BufferedReader(ent);
            String linha;
            String[] campos = null;
            while ((linha = br.readLine()) != null) {
                campos = linha.split(";");
                String nomeLista = campos[1];
                String cpfLista = campos[2];
                String dataNascimentoLista = campos[3];
                float craLista = Float.parseFloat(campos[4]);
                //por algum motivo == não confiona nisso aqui, toda vez usar equals
                if(campos[0].equals("Graduando")) {
                    boolean estagioLista = false;
                    if(campos[5].equals("true")) estagioLista = true;
                    Graduando graduandoLista = new Graduando(cpfLista,nomeLista, dataNascimentoLista, craLista, estagioLista);
                    estudantes.add(graduandoLista);
                }else if(campos[0].equals("PosGraduando")){
                    PosGraduando posGraduandoLista = new PosGraduando( cpfLista,nomeLista, dataNascimentoLista, craLista, campos[5]);
                    estudantes.add(posGraduandoLista);
                }
            }
            br.close();
        } catch (IOException erro) {
            System.out.println("Erro na leitura dos dados");
        }
        return estudantes;

    }

    //Disciplina já está certo
    public static List<Disciplina> leituraDisciplinas(){
        List<Disciplina> disciplina = new ArrayList<>();
        try {
            Disciplina aux;
            FileReader ent = new FileReader("Arquivos/Disciplinas.txt");
            BufferedReader br = new BufferedReader(ent);
            String linha;
            String[] campos = null;
            while ((linha = br.readLine()) != null) {
                campos = linha.split(";");
                String codigoLista = campos[0];
                String nomeDisciplina = campos[1];
                int cargaHoraria = Integer.parseInt(campos[2]);
                aux = new Disciplina( codigoLista,nomeDisciplina, cargaHoraria);
                disciplina.add(aux);
            }
            br.close();
        } catch (IOException erro) {
            System.out.println("Erro na leitura dos dados");
        }
        return disciplina;
    }

    //Tudo certo
    public static List<Professor> leituraProfessores(){
        List<Professor> professor = new ArrayList<>();
        try {
            Professor aux;
            FileReader ent = new FileReader("Arquivos/Professores.txt");
            BufferedReader br = new BufferedReader(ent);
            String linha;
            String[] campos = null;
            while ((linha = br.readLine()) != null) {
                campos = linha.split(";");
                String cpfProfessor = campos[0];
                String nomeProfessor = campos[1];
                String dataNascimentoProfessor = campos[2];
                int inicioContratoProfessor = Integer.parseInt(campos[3]);
                String departamentoProfessor = campos[4];
                aux = new Professor(cpfProfessor,nomeProfessor, dataNascimentoProfessor, inicioContratoProfessor, departamentoProfessor);
                professor.add(aux);
            }
            br.close();
        } catch (IOException erro) {
            System.out.println("Erro na leitura dos dados");
        }
        return professor;

    }

    //Escritas exceto turma
    public static void escritaEstudante(Estudante estudanteNovo) {
        String finalLinha = null;
        String linhaNova = null;
        if(estudanteNovo instanceof Graduando){
            linhaNova = "Graduando;";
            if(((Graduando) estudanteNovo).getEstagioSupervisionado()) finalLinha = "true;";
            else  finalLinha = "false;";
        }else {
            linhaNova = "PosGraduando;";
            finalLinha = ((PosGraduando) estudanteNovo).getTemaDePesquisa() + ";";
        }
        linhaNova = "\n"+ linhaNova + estudanteNovo.getNome() + ";" + estudanteNovo.getCpf() + ";" +estudanteNovo.getDataNascimento() + ";" + estudanteNovo.getCra() + ";" + finalLinha;
        try {
            FileWriter arq = new FileWriter("Arquivos/Alunos.txt", true);
            PrintWriter out = new PrintWriter(arq);
            out.print(linhaNova);
            out.close();
        } catch (IOException erro) {
            System.out.println("Erro na escrita dos dados");
        }
    }

    public static void escritaProfessores(Professor professorNovo) {
        String linhaNova = null;

        linhaNova = "\n"+ professorNovo.getCpf() + ";" + professorNovo.getNome() + ";" + professorNovo.getDataNascimento() + ";" + professorNovo.getInicioDoContrato() + ";" + professorNovo.getDepartamentoVinculado() + ";";
        try {
            FileWriter arq = new FileWriter("Arquivos/Professores.txt", true);
            PrintWriter out = new PrintWriter(arq);
            out.print(linhaNova);
            out.close();
        } catch (IOException erro) {
            System.out.println("Erro na escrita dos dados");
        }
    }

    public static void escritaDisciplinas(Disciplina disciplinaNova) {
        String linhaNova = null;

        linhaNova = "\n" + disciplinaNova.getCodigo() + ";" + disciplinaNova.getNomeDisciplina() + ";" + disciplinaNova.getCargaHoraria() + ";";
        try {
            FileWriter arq = new FileWriter("Arquivos/Disciplinas.txt", true);
            PrintWriter out = new PrintWriter(arq);
            out.print(linhaNova);
            out.close();
        } catch (IOException erro) {
            System.out.println("Erro na escrita dos dados");
        }
    }

    //Ultima cosia a ser feita
    public static List<Turma> leituraTurmas(List<Professor> professores, List<Estudante> estudantes, List<Disciplina> disciplinas){
        List<Turma> turma = new ArrayList<>();
        try {
            FileReader ent = new FileReader("Arquivos/Turmas.txt");
            BufferedReader br = new BufferedReader(ent);
            String linha;
            List<Estudante> est = new ArrayList<>();
            Estudante aux;
            while ((linha = br.readLine()) != null) {
            	String[] campos = null;
            	est.clear();
                campos = linha.split(";");
                String codigoDisciplina = campos[0];
                int ano = Integer.parseInt(campos[1]);
                int semestre = Integer.parseInt(campos[2]);
                String cpfProfessor =  campos[3];
                Professor prof = Busca.procuraProfessor(professores, cpfProfessor);
                Disciplina disc = Busca.procuraDisciplina(disciplinas, codigoDisciplina);
                for(int i= 4; i < campos.length; i++) {
                    aux = Busca.procuraEstudante(estudantes, campos[i]);
                    est.add(aux);
                }
                Turma turmaAux = new Turma(disc, ano, semestre, prof, est);
                turma.add(turmaAux);
            }
            
            br.close();
        } catch (IOException erro) {
            System.out.println("Erro na leitura dos dados");
        }
        return turma;
    }

    public static void escritaTurmas(Turma turma) {
        String linhaNova = null;
        //Sem condicoes colocar tudo na mesma linha
        linhaNova = "\n"+ turma.getDisciplina().getCodigo() + ";" +
                turma.getAno() + ";" +
                turma.getSemestre() + ";" +
                turma.getProfessor().getCpf() + ";";
        for(Estudante est: turma.getEstudantes()) {
            if(est == null) break;
            linhaNova += est.getCpf() + ";";
        }

        try {
            FileWriter arq = new FileWriter("Arquivos/Turmas.txt", true);
            PrintWriter out = new PrintWriter(arq);
            out.print(linhaNova);
            out.close();
        } catch (IOException erro) {
            System.out.println("Erro na escrita dos dados");
        }
    }

}