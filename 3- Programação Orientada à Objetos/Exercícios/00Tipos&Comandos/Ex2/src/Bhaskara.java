public class Bhaskara {

    public static double getCoeficientValue(char coefficientLabel) {

        double coefficietValue = 0.0;
        boolean validInput = false;

        while (!validInput) {
            try {
                coefficietValue = EntradaTeclado.leDouble();
                validInput = true;
            } catch (Exception e) {
                System.out.printf("Digite um valor numérico válido para %c: ", coefficientLabel);
                validInput = false;
            }
        }

        return coefficietValue;
    }


    public static void main (String[] args) {

        System.out.println("==== BHASKARA ====");

        System.out.print("Digite o valor do coeficiente a: ");
        double a = getCoeficientValue('a');

        System.out.print("Digite o valor do coeficiente b: ");
        double b = getCoeficientValue('b');

        System.out.print("Digite o valor do coeficiente c: ");
        double c = getCoeficientValue('c');

        double delta = Math.pow(b,2) - 4 * a * c;

        if (delta < 0) {
            System.out.println("A equação não possui soluções reais!");
        }
        else if (delta == 0) {
            double x = (b * (-1) + Math.sqrt(delta)) / (2 * a);
            System.out.printf("x = ± %.4f\n", x);
        }
        else {
            double x1 = (b * (-1) + Math.sqrt(delta)) / (2 * a);
            double x2 = (b * (-1) - Math.sqrt(delta)) / (2 * a);
            System.out.printf("x1 = %.4f\n", x1);
            System.out.printf("x2 = %.4f\n", x2);
        }
    }
}
