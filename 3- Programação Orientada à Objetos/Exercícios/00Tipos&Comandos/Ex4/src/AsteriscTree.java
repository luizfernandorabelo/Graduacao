public class AsteriscTree {

    public static int readNumberOfLines() {

        int numberOfLines = 0;
        boolean validInput = false;

        while (!validInput) {
            try {
                numberOfLines = EntradaTeclado.leInt();
                validInput = true;
            } catch (Exception e) {
                System.out.println("Digite um valor válido para o número de linhas: ");
                validInput = false;
            }
        }

        return numberOfLines;
    }

    public static void main(String[] args) {

        System.out.print("Digite o número de linhas: ");
        int numberOfLines = readNumberOfLines();

        for (int i = 0; i < numberOfLines; i++) {
            for (int j = 0; j < i; j++)
                System.out.print(" ");
            for (int j = numberOfLines - i; j > 0; j--)
                System.out.print("*");
            System.out.println();
        }
    }

}
