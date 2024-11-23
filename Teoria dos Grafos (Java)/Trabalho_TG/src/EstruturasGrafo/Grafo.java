package EstruturasGrafo;
import AlgoritmosBaseDados.AlgoritmosBaseDados;

import EstruturasGrafo.Aresta;
import EstruturasGrafo.Vertice;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Stack;

public class Grafo {

    private ArrayList<Aresta> arestas = new ArrayList<>();
    private ArrayList<Vertice> vertices = new ArrayList<>();
	
	public Grafo(ArrayList<Vertice> vertices){
		this.vertices = vertices;
	}
	
    public Grafo(){

	}
	
    public void insereValoresArestas(BigDecimal distanciaMediana) {    	
        AlgoritmosBaseDados algoritmos = new AlgoritmosBaseDados();
        BigDecimal distanciaVertices;
        for(Vertice vertice1: vertices) {
            for(Vertice vertice2: vertices) {
                if(!vertice1.equals(vertice2)) {
                    distanciaVertices = algoritmos.calcularDistanciaHaversine(vertice1, vertice2);
                    if(distanciaVertices.compareTo(distanciaMediana) <= 0) {
                    	//Insercao da aresta ao grafo, aresta incidente e vertice vizinho
                        Aresta arestaNova = new Aresta();
                        arestaNova.setOrigem(vertice1);
                        arestaNova.setDestino(vertice2);
                        arestaNova.setPeso(distanciaVertices);
                        arestas.add(arestaNova);
                        vertice2.adicionarArestaIncidente(arestaNova);
                        vertice2.adicionarVizinho(vertice1);
                    }
                }
            }
        }
    }
    
    public void imprimirVertices() {
        for (Vertice vertice : vertices) {
            System.out.println(vertice.getNomeLocalizacao()+ " " + vertice.getLatitude() + " "+ vertice.getLongitude());
        }
    }
    
    public void imprimirAresta() {
        for (Aresta aresta : arestas) {
            System.out.println(aresta.getOrigem().getNomeLocalizacao()+ " -> " + aresta.getDestino().getNomeLocalizacao());
        }
    }
    
    
    public ArrayList<Aresta> getArestas(){
    	return arestas;
    }
    
    public ArrayList<Vertice> getVertices(){
    	return vertices;
    }
    
}