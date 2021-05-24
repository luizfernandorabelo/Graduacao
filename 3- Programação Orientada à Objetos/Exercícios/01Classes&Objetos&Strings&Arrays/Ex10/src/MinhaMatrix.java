public class MinhaMatrix {

    public static int [][] leMatriz() {

        int numeroLinhas = EntradaPadrao.leInteiro("Digite o número de linhas da matriz: ");
        int numeroColunas = EntradaPadrao.leInteiro("Digite o número de colunas da matriz: ");

        int [][] matriz = new int[numeroLinhas][numeroColunas];

        for (int i = 0; i < numeroLinhas; i++) {
            for (int j = 0; j < numeroColunas; j++)
                matriz[i][j] = EntradaPadrao.leInteiro("Matriz[" + i + "][" + j + "]: ");
        }

        return matriz;
    }

    public static void substituiValores(int[][] matriz) {
        for(int i = 0; i < matriz.length; i++) {
            for(int j = 0; j < matriz[i].length; j++) {
                matriz[i][j] = matriz[i][j] % 2 == 0 ? 1 : -1;
            }
        }
    }

    public static void imprimeMatriz(int [][] matriz) {
        for(int i = 0; i < matriz.length; i++) {
            for(int j = 0; j < matriz[i].length; j++) {
                System.out.print(matriz[i][j] + "\t");
            }
            System.out.println();
        }
    }

}
