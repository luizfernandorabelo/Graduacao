public class Main {

    public static void main(String[] args) {

        // Criação de cds:
        Cd cd1 = new Cd(12345, "Parachutes", "Coldplay");
        Cd cd2 = new Cd(67890, "Viva la Vida", "Coldplay");
        Cd cd3 = new Cd(97531, "Twenty One", "Adele");

        // Criação de dvds:
        Dvd dvd1 = new Dvd(86420, "Vidas Secas", "Herbert Richards");
        Dvd dvd2 = new Dvd(24680, "Pinguins de Madagascar", "DreamWorks");

        // Criação de livros:
        Livro livro1 = new Livro(13579, "JK Rowling", "Harry Potter");
        Livro livro2 = new Livro(11111, "Yuval Noah Harari", "Sapiens");
        Livro livro3 = new Livro(98989, "George Orwell", "1984");

        // Adição dos produtos na loja:
        Loja.adicionarProduto(cd1, 5);
        Loja.adicionarProduto(cd2, 8);
        Loja.adicionarProduto(cd3, 10);
        Loja.adicionarProduto(dvd1, 1);
        Loja.adicionarProduto(dvd2, 4);
        Loja.adicionarProduto(livro1, 15);
        Loja.adicionarProduto(livro2, 11);
        Loja.adicionarProduto(livro3, 6);

        // Impressão do estoque inicial:
        System.out.println("\n>>> Estoque inicial:");
        Loja.mostrarEstoque();

        // Busca por código de barras:
        System.out.println("\n>>> Produto de código 13579: " + Loja.buscarProduto(13579).getNome());

        // Busca por nome:
        System.out.println("\n>>> Produto de nome \"Twenty One - Adele\" tem código: " + Loja.buscarProduto("Twenty One - Adele").getCodigo());

        // Impressão do estoque após remover alguns produtos:
        System.out.println("\n>>> Estoque após vender 1 unidade de Vida Secas e Viva la Vida:");
        Loja.venderProduto(67890);
        Loja.venderProduto(86420);
        Loja.mostrarEstoque();
    }

}
