import java.util.Arrays;

public class Loja {

    private static int capacidade = 1; // número de produtos que a loja é capaz de armazenar
    private static int totalProdutos = 0; // número de produtos diferentes que a loja armazena atualmente
    private static int quantidadeCds = 0; // soma de todas as quantidades de todos os cds presentes na loja
    private static int quantidadeDvds = 0; // soma de todas as quantidades de todos os dvds presentes na loja
    private static int quantidadeLivros = 0; // soma de todas as quantidades de todos os livros presentes na loja
    private static Produto[] produtos = new Produto[capacidade]; // conjunto dos diferentes produtos presentes na loja
    private static int[] quantidadesProdutos = new int[capacidade]; // quantidades de todos os diferentes produtos presentes na loja

    private static void garantirCapacidade() {
        if (totalProdutos == capacidade) {
            produtos = Arrays.copyOf(produtos, capacidade * 2);
            quantidadesProdutos = Arrays.copyOf(quantidadesProdutos, capacidade * 2);
            capacidade *= 2;
        }
    }

    public static void adicionarProduto(Produto produto, int quantidade) {

        garantirCapacidade();

        produtos[totalProdutos] = produto;
        quantidadesProdutos[totalProdutos++] = quantidade;

        if (produto instanceof Cd)
            quantidadeCds += quantidade;
        else if (produto instanceof Dvd)
            quantidadeDvds += quantidade;
        else
            quantidadeLivros += quantidade;
    }

    public static Produto buscarProduto(long codigo) {
        for (Produto produtoAtual : produtos) {
            if (produtoAtual.codigo == codigo)
                return produtoAtual;
        }
        return null;
    }

    public static Produto buscarProduto(String nome) {
        for (Produto produtoAtual : produtos) {
            if (produtoAtual.nome.equals(nome))
                return produtoAtual;
        }
        return null;
    }

    private static void removerUnidade(int indiceRemovido) {

        quantidadesProdutos[indiceRemovido]--;

        if (produtos[indiceRemovido] instanceof Cd)
            quantidadeCds--;
        else if (produtos[indiceRemovido] instanceof Dvd)
            quantidadeDvds--;
        else
            quantidadeLivros--;

        if (quantidadesProdutos[indiceRemovido] > 0)
            return;

        // Se não houver restado nenhuma unidade do produto, ele deve ser removido do conjunto de diferentes produtos:

        for (int i = indiceRemovido; i < totalProdutos - 1; i++) {
            produtos[i] = produtos[i+1];
            quantidadesProdutos[i] = quantidadesProdutos[i+1];
        }

        produtos[totalProdutos-1] = null;
        quantidadesProdutos[totalProdutos-1] = 0;
        totalProdutos--;
    }

    public static void venderProduto(long codigo) {
        for (int i = 0; i < totalProdutos; i++) {
            if (produtos[i].codigo == codigo) {
                removerUnidade(i);
                break;
            }
        }
    }

    public static void mostrarEstoque() {

        System.out.println("CATEG  QT    CÓDIGO    DESCRIÇÃO");

        for (int i = 0; i < totalProdutos; i++) {
            Produto produtoAtual = produtos[i];
            int quantidadeProdutoAtual = quantidadesProdutos[i];
            String linha =
                produtoAtual.categoria + "  " +
                String.format("%02d", quantidadeProdutoAtual) + "  " +
                String.format("%010d", produtoAtual.getCodigo()) + "  " +
                produtoAtual.getNome();
            System.out.println(linha);
        }

        String mensagemFinal = "O estoque possui " + totalProdutos + " diferentes produtos, contando com " +
               quantidadeCds + " cópias de CDs, " + quantidadeDvds + " cópias de DVDs e " + quantidadeLivros + " cópias de livros.";

        System.out.println(mensagemFinal);
    }

}
