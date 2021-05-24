public class Pedido {

    private String nomeProduto;
    private double valor;

    public String getNomeProduto() {
        return this.nomeProduto;
    }

    public double getValor() {
        return this.valor;
    }

    public void print() {
        System.out.printf("PRODUTO:\t%s\t\t", this.nomeProduto);
        System.out.printf("VALOR (R$):\t%f\n", this.valor);
    }

    public Pedido(String nomeProduto, double valor) {
        this.nomeProduto = nomeProduto;
        this.valor = valor;
    }

}
