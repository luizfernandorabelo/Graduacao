import java.io.IOException;

public class SquareRoot {

    public static void main(String[] args) throws IOException {

        final double ERROR_BOUND = 0.00000001;

        System.out.println("==== CALCULA RAIZ QUADRADA ====");

        System.out.print("Digite o valor do radicando: ");
        double radicand = EntradaTeclado.leDouble();

        if (radicand < 0) {
            System.out.println("∄ solução ∊ ℝ");
            System.exit(0);
        }

        System.out.print("Digite uma aproximação para o valor da raiz: ");
        double currentAproximation = EntradaTeclado.leDouble();

        if (currentAproximation <= 0 && radicand != 0) {
            System.out.println("A aproximação deve ser maior que 0");
            System.exit(0);
        }

        double previousAproximation = radicand / 2;

        while (Math.abs(currentAproximation - previousAproximation) >= ERROR_BOUND) {
            previousAproximation = currentAproximation;
            currentAproximation = (previousAproximation + radicand / previousAproximation) / 2;
        }

        System.out.printf("Valor aproximado = %f", currentAproximation);
    }

}