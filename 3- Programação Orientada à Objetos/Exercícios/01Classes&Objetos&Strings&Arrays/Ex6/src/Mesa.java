import java.util.ArrayList;

public class Mesa {

    private int numero;
    private String nomeCliente;
    private ArrayList<Pedido> pedidos = new ArrayList<Pedido>();
    private double conta = 0;

    public int getNumero() {
        return this.numero;
    }

    public String getNomeCliente() {
        return this.nomeCliente;
    }

    public Pedido getPedido(int numeroPedido) {
        Pedido pedido = null;
        try {
            pedido = this.pedidos.get(numeroPedido);
        } catch (Exception e) {
            System.out.println("Pedido não encontrado!");
        }
        return pedido;
    }

    public void adicionarPedido(Pedido novoPedido) {
        this.pedidos.add(novoPedido);
        this.conta += novoPedido.getValor();
    }

    public void print() {
        System.out.printf("NUMERO: \t%d\n", this.numero);
        System.out.printf("CLIENTE:\t%s\n", this.nomeCliente);
        for (Pedido pedidoAtual: pedidos)
            pedidoAtual.print();
        System.out.printf("TOTAL:  \t\t\t\t\t\t\t%f\n\n", this.conta);
    }

    public Mesa(int numero, String nomeCliente) {
        this.numero = numero;
        this.nomeCliente = nomeCliente;
    }

}
