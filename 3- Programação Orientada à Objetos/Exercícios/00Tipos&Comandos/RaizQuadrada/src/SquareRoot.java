import java.io.IOException;

public class SquareRoot {

    public static void main(String[] args) throws IOException {

        final double ERROR_BOUND = 0.00000001;

        System.out.print("Digite um númeor real: ");

        double radicand = EntradaTeclado.leDouble();
        double currRoot = 0.0;
        double previousRoot = 0.0;

        while (Math.pow(currRoot, 2.0) <= radicand)
            currRoot++;

        currRoot--;

        while (Math.abs(currRoot - previousRoot) >= ERROR_BOUND) {
            previousRoot = currRoot;
            currRoot = (previousRoot + radicand / previousRoot) / 2;
        }

        System.out.println(currRoot);
    }

}