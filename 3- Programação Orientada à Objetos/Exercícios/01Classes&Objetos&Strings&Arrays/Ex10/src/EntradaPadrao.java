import java.util.Scanner;

public class EntradaPadrao {

    static Scanner scanner = new Scanner(System.in);

    public static String leString(String label) {

        String stringLida = "";
        boolean inputValido = false;

        while (!inputValido) {
            try {
                System.out.print(label);
                stringLida = scanner.nextLine();
                inputValido = stringLida.length() > 0;
            } catch (Exception e) {
                System.out.println("Entrada inválida!");
                inputValido = false;
            }
        }

        return stringLida;
    }

    public static int leInteiro(String label) {

        int inteiroLido = 0;
        boolean inputValido = false;

        while (!inputValido) {
            try {
                inteiroLido = Integer.parseInt(leString(label));
                inputValido = true;
            } catch (Exception e) {
                System.out.println("Entrada inválida!!!");
                inputValido = false;
            }
        }

        return inteiroLido;
    }

    public static double leDouble(String label) {

        double doubleLido = 0;
        boolean inputValido = false;

        while (!inputValido) {
            try {
                doubleLido = Double.parseDouble(leString(label));
                inputValido = true;
            } catch (Exception e) {
                System.out.println("Entrada inválida!!!");
                inputValido = false;
            }
        }

        return doubleLido;
    }

}
