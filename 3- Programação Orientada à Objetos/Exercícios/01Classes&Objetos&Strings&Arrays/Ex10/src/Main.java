import javax.sound.midi.Soundbank;

public class Main {

    public static void main(String[] args) {

        int [][] matriz = MinhaMatrix.leMatriz();

        System.out.println("Matriz original: ");
        MinhaMatrix.imprimeMatriz(matriz);

        MinhaMatrix.substituiValores(matriz);

        System.out.println("Nova matriz: ");
        MinhaMatrix.imprimeMatriz(matriz);
    }

}
