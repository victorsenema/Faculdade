package EstruturasGrafo;
import java.math.BigDecimal;
import java.util.ArrayList;

public class Vertice {
	private BigDecimal latitude;
	private BigDecimal longitude;
	private String nomeLocalizacao;
	private ArrayList<Aresta> arestaIncidente = new ArrayList<Aresta>();
	private ArrayList<Vertice> vizinhos = new ArrayList<Vertice>();
	private boolean visitado = false;
	

	public Vertice(BigDecimal latitude, BigDecimal longitude, String nomeLocalizacao) {
		this.latitude = latitude;
		this.longitude = longitude;
		this.nomeLocalizacao  = nomeLocalizacao;
	}

	public Vertice(String NomeLocalizacao){
		this.setNomeLocalizacao(NomeLocalizacao);
	}
    
	public Vertice(){

	}

	public void setLatitude(BigDecimal latitude) {
		this.latitude = latitude;
	}
	
	public void setLongitude(BigDecimal longitude) {
		this.longitude = longitude;
	}
	
	public void setNomeLocalizacao(String nomeLocalizacao) {
		this.nomeLocalizacao = nomeLocalizacao;
	}
	
	public BigDecimal getLatitude() {
		return latitude;
	}
	
	public BigDecimal getLongitude() {
		return longitude;
	}
	
	public String getNomeLocalizacao() {
		return nomeLocalizacao;
	}

	public boolean isVisitado() {
		return visitado;
	}
	
	public void setVisitado(boolean visitado) {
		this.visitado = visitado;
	}

	public void adicionarArestaIncidente(Aresta aresta) {
		this.arestaIncidente.add(aresta);
	}
	
	public void adicionarVizinho(Vertice vertice) {
		this.vizinhos.add(vertice);
	}

	public int getGrauEntrada() {
        int grau = 0;
        for (Aresta aresta : arestaIncidente) {
            if (aresta.getDestino().equals(this)) {
                grau++;
            }
        }
        return grau;
    }

	public int getGrauSaida() {
        return vizinhos.size();
    }

	public ArrayList<Vertice> getVizinhos() {
        return vizinhos;
    }

    public void removerVizinho(Vertice vizinho) {
        vizinhos.remove(vizinho);
    }
    
    public ArrayList<Aresta> getArestaIncidente(){
    	return arestaIncidente;
    }

}
