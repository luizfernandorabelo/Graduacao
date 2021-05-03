public class Prime {

    public static int readIntegerNumber() {

        int integerNumber = 0;
        boolean validInput = false;

        while (!validInput) {
            try {
                integerNumber = EntradaTeclado.leInt();
                validInput = true;
            } catch (Exception e) {
                System.out.print("Digite um inteiro válido: ");
                validInput = false;
            }
        }

        return integerNumber;
    }

    public static boolean isPrime(int number) {

        int numberSqrt = (int) Math.sqrt(number);

        if (number < 2)
            return false;
        else if (number == 2)
            return true;

        for (int i = 2; i <= numberSqrt; i++) {
            if (number % i == 0)
                return false;
        }

        return true;
    }

    public static void main(String[] args) {

        System.out.print("Digite um número inteiro: ");
        int number = readIntegerNumber();

        if (number <= 2)
            System.out.printf("Não existe número primo que anteceda %d", number);
        else {
            for (int i = number - 1; i >= 2; i--)
               if (isPrime(i)) {
                   System.out.printf("O primeiro primo que antecede %d é %d", number, i);
                   break;
               }
        }
    }

}
