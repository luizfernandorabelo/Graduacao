public class Main {

    public static Circulo criarCirculo(String cor, boolean preenchido) {

        Circulo novoCirculo = null;

        while (novoCirculo == null) {
            double raioLido = EntradaPadrao.leDouble("Digite o valor do raio do círculo: ");
            try {
                novoCirculo = new Circulo(raioLido, cor, preenchido);
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
                novoCirculo = null;
            }
        }

        return novoCirculo;
    }

    public static Quadrado criarQuadrado(String cor, boolean preenchido) {

        Quadrado novoQuadrado = null;

        while (novoQuadrado == null) {
            double ladoLido = EntradaPadrao.leDouble("Digite o valor do lado do quadrado: ");
            try {
                novoQuadrado = new Quadrado(ladoLido, cor, preenchido);
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
                novoQuadrado = null;
            }
        }

        return novoQuadrado;
    }

    public static Retangulo criarRetangulo() {

        Retangulo novoRetangulo = null;

        while (novoRetangulo == null) {
            double baseLida = EntradaPadrao.leDouble("Digite o valor da base do retângulo: ");
            double alturaLida = EntradaPadrao.leDouble("Digite o valor da altura do retângulo: ");
            try {
                novoRetangulo = new Retangulo(baseLida, alturaLida);
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
                novoRetangulo = null;
            }
        }

        return novoRetangulo;
    }

    public static void main(String[] args) {

        // Criação das figuras com dimensões lidas da entrada padrão:
        Circulo meuCirculo = criarCirculo("azul", true);
        Quadrado meuQuadrado = criarQuadrado("vermelho", false);
        Retangulo meuRetangulo = criarRetangulo(/*transparente*/);

        // Cálculo e impressão das áreas e dos perímetros:
        System.out.println("\nFigura: " + meuCirculo);
        System.out.println("Área = " + String.format("%.2f", meuCirculo.calcularArea()));
        System.out.println("Perímetro = " + String.format("%.2f", meuCirculo.calcularPerimetro()));

        System.out.println("\nFigura: " + meuQuadrado);
        System.out.println("Área = " + String.format("%.2f", meuQuadrado.calcularArea()));
        System.out.println("Perímetro = " + String.format("%.2f", meuQuadrado.calcularPerimetro()));

        System.out.println("\nFigura: " + meuRetangulo);
        System.out.println("Área = " + String.format("%.2f", meuRetangulo.calcularArea()));
        System.out.println("Perímetro = " + String.format("%.2f", meuRetangulo.calcularPerimetro()));

    }

}
