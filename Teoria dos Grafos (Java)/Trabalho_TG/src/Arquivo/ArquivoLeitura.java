package Arquivo;

import EstruturasGrafo.Vertice;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.List;

public class ArquivoLeitura {

    public static ArrayList<Vertice> leituraArquivo() {
        String ultimaLinha = null;
        ArrayList <Vertice> vertices = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader("src/Arquivo/Codigo_Pagina.txt"))) {
            String linha;
            while ((linha = br.readLine()) != null) {
                ultimaLinha = linha; // Atualiza a última linha
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        //Retirar as informações inuteis da priemira linha
        String[] recorteDadosBrutos = ultimaLinha.split("\\[\\[\\[");
        
        //Separando as Coordenadas e o Nome do ponto

        for (int i = 4, j = 0; i < recorteDadosBrutos.length - 1; i++, j++) {
        	//Separando informações por vírgula
        	String[] recorteInfoVertices = recorteDadosBrutos[i].split(",");
        	//Latitude
        	String latitude = recorteInfoVertices[0];
        	//Longitude retirando os caracteres "]]]"
            String longitude = recorteInfoVertices[1].substring(0, recorteInfoVertices[1].length() - 3);
            //
            String nome = recorteInfoVertices[6].substring(3, recorteInfoVertices[6].length() - 3);
            
            //inserindo informações no vertice
            Vertice verticeNovo = new Vertice();
            verticeNovo.setLatitude(new BigDecimal(latitude));
            verticeNovo.setLongitude(new BigDecimal(longitude));
            verticeNovo.setNomeLocalizacao(nome);
            vertices.add(verticeNovo);
        }
        
        return vertices;
    }
    
}