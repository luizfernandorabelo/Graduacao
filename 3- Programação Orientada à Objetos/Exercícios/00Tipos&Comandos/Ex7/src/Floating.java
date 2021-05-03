public class Floating {

    public static double readDouble() {

        double number = 0.0;
        boolean validInput = false;

        while (!validInput) {
            try {
                number = EntradaTeclado.leDouble();
                validInput = true;
            } catch (Exception e) {
                System.out.print("Digite um valor válido: ");
                validInput = false;
            }
        }

        return number;
    }

    public static void main(String[] args) {

        System.out.println("Digite a sequência de núeros: ");

        double currentNumber = readDouble();
        double lowestNumber = currentNumber;
        double highestNumber = currentNumber;

        while (currentNumber != 0.0){
            if (currentNumber < lowestNumber)
                lowestNumber = currentNumber;
            else if (currentNumber > highestNumber)
                highestNumber = currentNumber;
            currentNumber = readDouble();
        }

        System.out.printf("O menor número digitado foi %f\n", lowestNumber);
        System.out.printf("O maior número digitado foi %f\n", highestNumber);
    }

}
