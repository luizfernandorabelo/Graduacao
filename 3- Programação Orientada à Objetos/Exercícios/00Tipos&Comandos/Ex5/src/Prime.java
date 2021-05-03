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

    public static void main(String[] args) {

        System.out.print("Digite um número inteiro: ");
        int number = readIntegerNumber();

        int numberSqrt = (int) Math.sqrt(number);

        if (number < 2)
            System.out.printf("Não existem números primos menores que 2. Portanto, o número %d não é primo", number);
        else if (number == 2)
            System.out.println("2 é o único par primo");
        else {
            for (int i = 2; i <= numberSqrt; i++) {
                if (number % i == 0) {
                    System.out.printf("O número %d não é primo. Seu primeiro divisor é %d", number, i);
                    break;
                }
                if (i == numberSqrt) {
                    System.out.printf("O número %d é primo", number);
                }
            }
        }
    }

}
