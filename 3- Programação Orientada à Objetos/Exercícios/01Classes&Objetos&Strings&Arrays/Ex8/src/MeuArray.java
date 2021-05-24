public class MeuArray {

    public static int [] leArranjo() {
        
        int tamanhoArranjo = EntradaPadrao.leInteiro("Digite o tamanho do arranjo: ");
        int [] arranjo = new int[tamanhoArranjo];

        for (int i = 0; i < tamanhoArranjo; i++)
            arranjo[i] = EntradaPadrao.leInteiro("Arranjo[" + i + "]: ");

        return arranjo;
    }

    public static int getIndiceMaiorValor(int []arranjo) {

        int maiorIndice = 0;
        int tamanhoArranjo = arranjo.length;

        for (int indiceAtual = 1; indiceAtual < tamanhoArranjo; indiceAtual++)
            if (arranjo[indiceAtual] > arranjo[maiorIndice])
                maiorIndice = indiceAtual;

        return maiorIndice;
    }

}
