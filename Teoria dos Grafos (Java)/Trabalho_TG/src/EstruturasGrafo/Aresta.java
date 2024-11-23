package EstruturasGrafo;

import java.math.BigDecimal;

public class Aresta {

	private BigDecimal peso;
	private Vertice origem;
	private Vertice destino;
	private boolean visitado = false;
	
	
	public Aresta(BigDecimal peso, Vertice origem, Vertice destino) {
		this.setPeso(peso);
		this.setOrigem(origem);
		this.setDestino(destino);
	}
	
	public Aresta() {}
	
	public boolean isVisitado() {
		return visitado;
	}

	public void setVisitado(boolean visitado) {
		this.visitado = visitado;	
	}

	public BigDecimal getPeso() {
		return peso;
	}

	public void setPeso(BigDecimal peso) {
		this.peso = peso;
	}

	public Vertice getOrigem() {
		return origem;
	}

	public void setOrigem(Vertice origem) {
		
		this.origem = origem;
	}

	public void setDestino(Vertice destino) {
		
		this.destino = destino;
	}
	
	public Vertice getDestino() {
		return destino;
	}
	
	@Override
	public String toString() {
		String s = " ";
		s+= this.getOrigem().getNomeLocalizacao() + this.getDestino().getNomeLocalizacao();
		return s;
	}

}