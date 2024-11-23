package AlgoritmosBaseDados;
import EstruturasGrafo.Aresta;
import EstruturasGrafo.Vertice;
import java.util.ArrayList;
import java.util.Collections;
import java.math.BigDecimal;
import java.math.MathContext;

public class AlgoritmosBaseDados {
	
	//Escolha de 40% aleatório dos vertices
	public ArrayList escolhaAleatoriaVertices(ArrayList<Vertice> verticesGerados) {
		
		int quantiaVerticesRandom = (int) (verticesGerados.size() * 0.4);
		ArrayList<Vertice> verticesAleatorios = new ArrayList<Vertice>();
		
		Collections.shuffle(verticesGerados);
		for (int i = 0; i < quantiaVerticesRandom; i++) {
            verticesAleatorios.add(verticesGerados.get(i));
        }
	  
		return verticesAleatorios;
	}
	
	public BigDecimal medianaDistancias(ArrayList<Vertice> verticesGerados) {
		//ArrayList<Vertice> verticesAleatorios = escolhaAleatoriaVertices(verticesGerados);
		
		//Array de vertices para um valor mediano
		ArrayList<BigDecimal> distanciasEntreVertices = new ArrayList<BigDecimal>();
		int i = 0;
		BigDecimal distancia;
		
		for(Vertice vertice1 : verticesGerados) {
			for(Vertice vertice2 : verticesGerados){
				if(vertice2 != vertice1) {
					distancia = calcularDistanciaHaversine(vertice1, vertice2);
					distanciasEntreVertices.add(distancia);
					//System.out.println("Distancia: " + distanciasEntreVertices.get(i));
					i++;
				}
			}
		}
		Collections.sort(distanciasEntreVertices);
		/*
		for(BigDecimal result: distanciasEntreVertices) {
			System.out.println(result);
		}
		*/
		//System.out.println("Max: " + distanciasEntreVertices.get(distanciasEntreVertices.size() - 1));
		int indiceMediana = (int) (distanciasEntreVertices.size() * 0.7);
		return distanciasEntreVertices.get(indiceMediana);
	}
	
	
    public BigDecimal bigDeciParaRadianos(BigDecimal grausCoordenada) {
    	//Função necessária pois as funções já existentes não transformam o BigDecimal em Radianos
        BigDecimal pi = new BigDecimal(Math.PI);
        BigDecimal radianos = grausCoordenada.multiply(pi).divide(new BigDecimal(180), MathContext.DECIMAL128);
        return radianos;
    }
    
     public BigDecimal calcularDistanciaHaversine(Vertice vertice1, Vertice vertice2) {
        BigDecimal latitudeP1 = bigDeciParaRadianos((vertice1.getLatitude()));
        BigDecimal longitudeP1 = bigDeciParaRadianos(vertice1.getLongitude());
        BigDecimal latitudeP2 = bigDeciParaRadianos((vertice2.getLatitude()));
        BigDecimal longitudeP2 = bigDeciParaRadianos((vertice2.getLongitude()));

        BigDecimal diferencaLatitude = latitudeP2.subtract(latitudeP1);
        BigDecimal diferencaLongitude = longitudeP2.subtract(longitudeP1);

        // Fórmula de Haversine
        BigDecimal a = new BigDecimal(Math.pow(Math.sin(diferencaLatitude.doubleValue() / 2), 2))
                        .add(BigDecimal.valueOf(Math.cos(latitudeP1.doubleValue()))
                        .multiply(BigDecimal.valueOf(Math.cos(latitudeP2.doubleValue())))
                        .multiply(new BigDecimal(Math.pow(Math.sin(diferencaLongitude.doubleValue() / 2), 2))));

        BigDecimal c = new BigDecimal(2 * Math.atan2(Math.sqrt(a.doubleValue()), Math.sqrt(1 - a.doubleValue())));
        
        // Raio médio da Terra em metros
        BigDecimal raioTerra = BigDecimal.valueOf(6371000); // em metros
        
        // Calcula a distância em metros
        BigDecimal distanciaMetros = raioTerra.multiply(c);

        return distanciaMetros;
    }
}