package Pessoa;
import Dados_Pessoais.*;
import Exceptions.CpfInvalidoException;


public abstract class Pessoa {
	private String cpf;
	private String nome;
	private String dataNascimento;
	
	
	public abstract String imprimeDados();

	public Pessoa(String cpf, String nome, String dataNascimento) {
		setCpf(cpf);
		this.nome = nome;
		this.dataNascimento = dataNascimento;
	}	

	

	public String getCpf() {
		return cpf;
	}

	public void setCpf(String cpf) {
		try {
			if(ValidaCPF.isCPF(cpf)) {
				this.cpf = new String(cpf);
			}
			else {
				throw new CpfInvalidoException("CPF inválido.");
			}
		} catch (CpfInvalidoException e) {
			System.out.println(e);
		}
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getDataNascimento() {
		return dataNascimento;
	}

	public void setDataNascimento(String dataNascimento) {
		this.dataNascimento = dataNascimento;
    }
	
}
