public class NewtonRaphsonMethod {

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

    public static double fPrime(double x) { // f'(x) = 3x² -2x - 13
        return 3 * Math.pow(x, 2) - 2 * x - 13;
    }

    public static void main(String[] args) {

        final double ERROR_BOUND = 10e-7;

        System.out.print("Chute inicial: ");
        double x0 = readDouble();

        int iterationCounter = 0;

        while (Math.abs(f(x0)) > ERROR_BOUND) {
            x0 = x0 - f(x0) / fPrime(x0);
            iterationCounter++;
        }

        System.out.printf("Nesse intervalo, f(x) = x³ - x² - 13x + 8 tem raíz em x ≅ %f\n", x0);
        System.out.printf("Aproximação obtida com %d iterações com o método de Newton-Raphson\n", iterationCounter);
    }

}
