package EstruturasGrafo;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Collections;

public class hamilton {

    public ArrayList<Vertice> encontrarCaminhoHamiltoniano(Grafo grafo, int indiceInicial) {
        ArrayList<Vertice> caminho = new ArrayList<>();
        Vertice pontoInicial = grafo.getVertices().get(indiceInicial);

        //Veirficacao de caminho hamilton
        if (verificarCaminhoHamiltoniano(grafo, pontoInicial, caminho)) {
        	//Grafo inverto
            Collections.reverse(caminho);
            return caminho;
        } else {
            return null;
        }
    }

    private boolean verificarCaminhoHamiltoniano(Grafo grafo, Vertice atual, ArrayList<Vertice> caminho) {
        //Vertice atual ao caminho hamilto
    	caminho.add(atual);

        //if se o caminho ja passou por todos os vertices
        if (caminho.size() == grafo.getVertices().size()) {
        	//if se tem aresta do ultimo vertice até o inicial
            if (atual.getVizinhos().contains(caminho.get(0))) {
            	//Adiciona vertice ao caminhp
                caminho.add(caminho.get(0));
                return true;
            } else {
            	//remove o vertice
                caminho.remove(atual);
                return false;
            }
        }

        //procura vertice n visitgado
        for (Vertice vizinho : atual.getVizinhos()) {
            if (!caminho.contains(vizinho)) {
                if (verificarCaminhoHamiltoniano(grafo, vizinho, caminho)) {
                    return true;
                }
            }
        }
        
        //Remove o vertice atual do caminho
        caminho.remove(atual);
        //entao nao encotro o caminho
        return false;
    }
}