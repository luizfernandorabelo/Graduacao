public class MinhaString {

    public String original;

    public void imprimeInvertida() {

        System.out.print("A string " + original + " ao contrário fica: ");

        int tamanhoOriginal = original.length();

        for (int i = tamanhoOriginal - 1; i >= 0; i--)
            System.out.print(original.charAt(i));

        System.out.println();
    }

    public void imprimeDigitos() {

        int tamanhoOriginal = original.length();

        System.out.print("A string " + original + " é formada pelos dígitos: ");

        for (int i = 0; i < tamanhoOriginal - 1; i++) {
            DigitoPorExtenso.print(original.charAt(i));
            System.out.print(", ");
        }

        System.out.print("e ");
        DigitoPorExtenso.print(original.charAt(tamanhoOriginal-1));
    }

    boolean ehPalindromo() {

        int primeiraPosicao = 0;
        int ultimaPosicao = original.length() - 1;

        while (primeiraPosicao < ultimaPosicao) {
            if (original.charAt(primeiraPosicao) != original.charAt(ultimaPosicao))
                return false;
            primeiraPosicao++;
            ultimaPosicao--;
        }

        return true;
    }

    public MinhaString(String original) {
        this.original = original;
    }

}
