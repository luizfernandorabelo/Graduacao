public class BisectionMethod {

    public static double readDouble() {

        double number = 0.0;
        boolean validInput = false;

        while (!validInput) {
            try {
                number = EntradaTeclado.leDouble();
                validInput = true;
            } catch (Exception e) {
                System.out.print("Digite um número válido: ");
                validInput = false;
            }
        }

        return number;
    }

    public static double f(double x) { // f(x) = x³ - x² - 13x + 8
        return Math.pow(x, 3) - Math.pow(x, 2) - 13 * x + 8;
    }

    public static void main(String[] args) {

        final double ERROR_BOUND = 10e-7;

        System.out.print("Início do intervalo: ");
        double minRange = readDouble();

        System.out.print("Fim do intervalo: ");
        double maxRange = readDouble();

        if (f(minRange) < f(maxRange)) {
            double temp = maxRange;
            maxRange = minRange;
            minRange = temp;
        }

        double x0 = (minRange + maxRange) / 2;

        int iterationCounter = 0;

        while (Math.abs(f(x0)) > ERROR_BOUND && iterationCounter < 100) {
            minRange = f(x0) > 0 ? x0 : minRange;
            maxRange = f(x0) < 0 ? x0 : maxRange;
            x0 = (minRange + maxRange) / 2;
            iterationCounter++;
        }

        if (iterationCounter >= 100)
            System.out.println("Não foi possível encontrar raiz de f(x) = x³ - x² - 13x + 8 nesse intervalo");
        else {
            System.out.printf("Nesse intervalo, f(x) = x³ - x² - 13x + 8 tem raíz em x ≅ %f\n", x0);
            System.out.printf("Aproximação obtida com %d iterações com o método da bisecção\n", iterationCounter);
        }
    }

}
