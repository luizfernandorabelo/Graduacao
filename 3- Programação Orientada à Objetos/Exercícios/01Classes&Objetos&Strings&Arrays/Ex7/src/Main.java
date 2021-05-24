public class Main {

    public static void main(String[] args) {

        MinhaString string1 = new MinhaString("socorrammesubinoonibusemmarrocos");

        string1.imprimeInvertida();

        System.out.print("Portanto, ");
        if (string1.ehPalindromo())
            System.out.println("é um palíndromo!");
        else
            System.out.println("não é um palíndromo!");
        System.out.println();

        MinhaString string2 = new MinhaString("1234567890");

        string2.imprimeDigitos();
    }

}
