package Arquivos;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import Dados_Graduacao.*;

public class main {
	public static void main(String[] args) {
		//Victor Gava Senema - 12211BCC041
		//Gustavo Henrique Barbosa Rocha - 12311BCC021
		//Fernando Favaro Henriques Netto - 12311BCC006 
		int op;
		List<Estudante> listaEstudantes = new ArrayList<>();
		List<Professor> listaProfessores = new ArrayList<>();
		List<Turma> listaTurmas = new ArrayList<>();
		List<Disciplina> listaDisciplinas = new ArrayList<>();
		Scanner scanner = new Scanner(System.in);

		//Leitura dos dados
		listaEstudantes = GerenciadorArquivos.leituraEstudantes();
		listaDisciplinas = GerenciadorArquivos.leituraDisciplinas();
		listaProfessores = GerenciadorArquivos.leituraProfessores();
		listaTurmas = GerenciadorArquivos.leituraTurmas(listaProfessores, listaEstudantes, listaDisciplinas);

		do {
			System.out.println("[1]: Cadastrar");
			System.out.println("[2]: Consultar");
			System.out.println("[3]: Sair");
			System.out.println("Opção: ");
			op = scanner.nextInt();

			switch (op) {
				case 1:
					int op2;
					do {
						System.out.println("\n[1]: Cadastrar Estudante");
						System.out.println("[2]: Cadastrar Professor");
						System.out.println("[3]: Cadastrar Disciplina");
						System.out.println("[4]: Cadastrar Turma");
						System.out.println("[5]: Cancelar");
						System.out.println("Opção: ");
						op2 = scanner.nextInt();

						switch (op2) {
							case 1:

								int ope;

								do {
									System.out.println("Tipo de Aluno");
									System.out.println("[1]: Graduando");
									System.out.println("[2]: Pos Graduando");
									System.out.println("[3]: Sair");
									ope = scanner.nextInt();
									switch (ope) {
										case 1:
											System.out.println("\nCadastro Graduando:");
											scanner.nextLine();
											Estudante estudante;
											String cpfG;
											do{
												System.out.println("Digite o CPF: ");
												cpfG = scanner.nextLine();
												estudante = Busca.procuraEstudante(listaEstudantes, cpfG);
												if(estudante != null) {
													System.out.println("ERRO! Cpf ja cadastrado");
												}
											}while(estudante != null);
											System.out.println("Digite o nome: ");
											String nomeG = scanner.nextLine();
											System.out.println("Digite a Data de Nascimento: ");
											String dataNascimentoG = scanner.nextLine();
											System.out.println("Digite o CRA: ");
											float craG= scanner.nextFloat();
											System.out.println("Faz estagio:");
											boolean estagioSupervisionado = scanner.nextBoolean();
											Graduando g = new Graduando(cpfG, nomeG, dataNascimentoG,craG, estagioSupervisionado);
											if(g.getCpf() != null) {
												listaEstudantes.add(g);
												GerenciadorArquivos.escritaEstudante(g);
											}
											break;
										case 2:
											System.out.println("\nCadastro PosGraduando:");
											scanner.nextLine();
											Estudante estudante1;
											String cpfPos;
											do{
												System.out.println("Digite o CPF: ");
												cpfPos = scanner.nextLine();
												estudante1 = Busca.procuraEstudante(listaEstudantes, cpfPos);
												if(estudante1 != null) {
													System.out.println("ERRO! Cpf ja cadastrado");
												}
											}while(estudante1 != null);
											System.out.println("Digite o nome: ");
											String nomePos = scanner.nextLine();
											System.out.println("Digite a Data de Nascimento: ");
											String dataNascimentoPos = scanner.nextLine();
											System.out.println("Digite o CRA: ");
											float craPos = scanner.nextFloat();
											System.out.println("Faz Pesquisa:");
											String pesquisa = scanner.nextLine();
											PosGraduando p = new PosGraduando(cpfPos, nomePos, dataNascimentoPos, craPos, pesquisa);
											if(p.getCpf() != null) {
												listaEstudantes.add(p);
												GerenciadorArquivos.escritaEstudante(p);
											}
											break;
										default:
											break;

									}
								}while(ope != 3);
								break;
							case 2:
								System.out.println("\nCadastro Professor:");
								scanner.nextLine();//consumir o buffer
								Professor professor1;
								String cpf1 = null;
								do{
									System.out.println("Digite o CPF: ");
									cpf1 = scanner.nextLine();
									professor1 = Busca.procuraProfessor(listaProfessores, cpf1);
									if(professor1 != null) {
										System.out.println("ERRO! Cpf ja cadastrado");
									}
								}while(professor1 != null);
								System.out.println("Digite o nome: ");
								String nome1 = scanner.nextLine();
								System.out.println("Digite a Data de Nascimento: ");
								String dataNascimento1 = scanner.nextLine();
								System.out.println("Digite o ano do inicio do contrato: ");
								int inicioContrato = scanner.nextInt();
								System.out.println("Digite o departamento: ");
								scanner.nextLine();
								String departamento = scanner.nextLine();
								Professor p = new Professor(cpf1, nome1, dataNascimento1, inicioContrato, departamento);
								if(p.getCpf() != null) {
									listaProfessores.add(p);
									GerenciadorArquivos.escritaProfessores(p);
								}
								break;
							case 3:
								System.out.println("\nCadastro Disciplina:");
								scanner.nextLine();//consumir o buffer
								System.out.println("Nome:");
								String nome2 = scanner.nextLine();
								Disciplina disciplina1;
								String codigo;
								do{
									System.out.println("Codigo: ");
									codigo = scanner.nextLine();
									disciplina1 = Busca.procuraDisciplina(listaDisciplinas, codigo);
									if(disciplina1 != null) {
										System.out.println("ERRO! Codigo da disciplina ja esta cadastrado");
									}
								}while(disciplina1 != null);
								System.out.println("Carga Horaria: ");
								int carga = scanner.nextInt();
								Disciplina d = new Disciplina(codigo, nome2, carga);
								listaDisciplinas.add(d);
								GerenciadorArquivos.escritaDisciplinas(d);
								break;
							case 4:
								System.out.println("\nCadastro Turma:");
								scanner.nextLine(); //consumir o buffer
								System.out.println("Ano:");
								int ano = scanner.nextInt();
								System.out.println("Semestre: ");
								int semestre = scanner.nextInt();
								scanner.nextLine();//consumir o buffer
								System.out.println("Lista de disciplinas:");
								for(Disciplina di : listaDisciplinas)
									di.mostra();
								System.out.println("Codigo da Disciplina: ");
								String d1 = scanner.nextLine();
								Disciplina disciplina = null;
								for (Disciplina di : listaDisciplinas) {
									if (d1.equals(di.getCodigo())) {
										disciplina = di;
										break;
									}
								}
								System.out.println("Lista de Professores");
								for (Professor pi : listaProfessores)
									pi.mostra();
								scanner.nextLine();
								System.out.println("Professor: ");
								String p1 = scanner.nextLine();
								Professor professor = null;
								for (Professor pi : listaProfessores) {
									if (p1.equals(pi.getCpf())) {
										professor = pi;
										break;
									}
								}

								int opcte;

								List<Estudante> listaEstudantes1 = new ArrayList<>();
								Turma t = new Turma(disciplina, ano, semestre, professor,listaEstudantes1);
								listaTurmas.add(t);

								for(Estudante li : listaEstudantes){
									li.mostra();
								}
								do{


									System.out.println("Adicionar Aluno");
									System.out.println("[1] Adiocionar Aluno");
									System.out.println("[2] Sair");
									opcte = scanner.nextInt();

									switch (opcte){
										case 1:

											System.out.println("Cpf do Aluno: ");
											scanner.nextLine();
											String e1 = scanner.nextLine();
											Estudante estudante = null;
											for (Estudante ei : listaEstudantes) {
												if (e1.equals(ei.getCpf())) {
													estudante = ei;
												}
											}
											if (estudante != null) {
												t.getEstudantes().add(estudante);
											} else {
												System.out.println("Estudante nao encontrado, tente novamente");
												break;
											}
											break;

										default:
											break;
									}

								}while (opcte != 2);

							default:
								break;
						}
					} while (op2 != 5);
					break;
				case 2:
					do {
						System.out.println("\n[1]: Consultar Estudante");
						System.out.println("[2]: Consultar Professor");
						System.out.println("[3]: Consultar Disciplina");
						System.out.println("[4]: Consultar Turma");
						System.out.println("[5]: Cancelar");
						System.out.println("Opção: ");
						op2 = scanner.nextInt();
						switch(op2) {
							case 1:
								for(Estudante e: listaEstudantes) {
									System.out.println(e.imprimeDados());
								}
								break;
							case 2:
								for(Professor p: listaProfessores) {
									System.out.println(p.imprimeDados());
								}
								break;
							case 3:
								for(Disciplina d: listaDisciplinas) {
									System.out.println(d.toString());
								}
								break;
							case 4:
								for(Turma t: listaTurmas) {
									t.mostraTurma();
								}
								break;

							default:
								break;
						}
					} while (op2 != 5);
					break;

				case 3:
					System.out.println("Tchau!");
					break;
				default:
					break;
			}
		} while (op != 3);
		scanner.close();
	}
}