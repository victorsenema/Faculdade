import Arquivo.ArquivoLeitura;
import EstruturasGrafo.Grafo;
import EstruturasGrafo.Vertice;
import java.math.BigDecimal;
import AlgoritmosBaseDados.AlgoritmosBaseDados;
import java.util.Scanner;
import EstruturasGrafo.hamilton;

import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        // Leitura dos vértices
        ArrayList<Vertice> vertices = ArquivoLeitura.leituraArquivo();
        // Grafo que vamos usar para ver o caminho
        Grafo grafo = new Grafo(vertices);
        // Objeto para fazer leitura de dados
        AlgoritmosBaseDados algoritmos = new AlgoritmosBaseDados();
        // Medida padrão para adicionar as arestas
        BigDecimal mediana = algoritmos.medianaDistancias(vertices);
        // Adicionar as informações ao grafo
        hamilton hamiltonPath = new hamilton();
        // Objeto para encontrar caminho hamiltoniano

        grafo.insereValoresArestas(mediana);
        // Criando um objeto Scanner para ler entrada do usuário
        Scanner scanner = new Scanner(System.in);
        
        for(int i = 0; i < grafo.getVertices().size(); i++) {
        	System.out.println("["+ i +"]: "+ grafo.getVertices().get(i).getNomeLocalizacao());
        }
        

        // Pedindo ao usuário para digitar um nome e transforma em indice
        System.out.println("Digite o Indice:");
        int indice = scanner.nextInt();
        
        // Encontrar o caminho hamiltoniano a partir do ponto inicial
        ArrayList<Vertice> caminhoHamiltoniano = hamiltonPath.encontrarCaminhoHamiltoniano(grafo, indice);
        
        BigDecimal distanciaTotal = new BigDecimal("0");
        BigDecimal divisor = new BigDecimal("1000");
        
        // Imprimir o caminho hamiltoniano encontrado
        if (caminhoHamiltoniano != null) {
            System.out.println("Caminho Hamiltoniano:");
            for (int i = 0; i < caminhoHamiltoniano.size(); i++) {
                System.out.print(caminhoHamiltoniano.get(i).getNomeLocalizacao() + " ");
                if(i != caminhoHamiltoniano.size() -1) {
                	distanciaTotal = distanciaTotal.add(algoritmos.calcularDistanciaHaversine(caminhoHamiltoniano.get(i), caminhoHamiltoniano.get(i+1)));
                	System.out.println(String.format(": (%.2f m)", algoritmos.calcularDistanciaHaversine(caminhoHamiltoniano.get(i), caminhoHamiltoniano.get(i+1)).doubleValue()));
                }
            }
            System.out.println("");
            BigDecimal distanciaEmKm = distanciaTotal.divide(divisor, 2, BigDecimal.ROUND_HALF_UP);
            System.out.println(String.format("Distância Total: %.2f km", distanciaEmKm.doubleValue()));
        } else {
            System.out.println("Não foi possível encontrar um caminho Hamiltoniano a partir do ponto inicial especificado.");
        }

    }
}