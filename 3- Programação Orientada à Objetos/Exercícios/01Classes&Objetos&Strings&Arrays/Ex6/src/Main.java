public class Main {

    public static void main(String[] args) {

        Mesa mesa1 = new Mesa(10, "Luiz");
        Pedido pedido1 = new Pedido("Água ", 3.00);
        mesa1.adicionarPedido(pedido1);

        Mesa mesa2 = new Mesa(11, "Ana");
        Pedido pedido2 = new Pedido("Pepsi", 5.00);
        Pedido pedido3 = new Pedido("Bauru", 7.00);
        mesa2.adicionarPedido(pedido2);
        mesa2.adicionarPedido(pedido3);

        mesa1.print();
        mesa2.print();

        System.out.println("O primeiro pedido de Ana foi " + mesa2.getPedido(0).getNomeProduto());
        System.out.println("E o segundo pedido de Ana foi " + mesa2.getPedido(1).getNomeProduto());
    }

}
