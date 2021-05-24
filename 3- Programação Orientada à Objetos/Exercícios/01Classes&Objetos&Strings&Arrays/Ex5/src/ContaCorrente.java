public class ContaCorrente {

    private int numeroConta;
    private String nomeBanco;
    private String nomeCliente;
    private double saldo;

    private boolean valorPositivo(double valor) {
        return valor > 0;
    }

    private boolean temSaldoSuficiente(double valorDebitado, double saldo) {
        return saldo >= valorDebitado;
    }

    private void imprimirMensagemErro() {
        System.out.println("Valor inválido!");
    }

    public void depositar(double valor) {
        if (!valorPositivo(valor)) {
            imprimirMensagemErro();
            return;
        }
        this.saldo += valor;
    }

    public void sacar(double valor) {
        if (!valorPositivo(valor) || !temSaldoSuficiente(valor, saldo)) {
            imprimirMensagemErro();
            return;
        }
        this.saldo -= valor;
    }

    public void transferir(ContaCorrente contaDestino, double valor) {
        if (!temSaldoSuficiente(valor, saldo) || !valorPositivo(valor)) {
            imprimirMensagemErro();
            return;
        }
        this.saldo -= valor;
        contaDestino.saldo += valor;
    }

    public void print() {
        System.out.printf("N° Conta:\t%d\n", this.numeroConta);
        System.out.printf("Cliente: \t%s\n", this.nomeCliente);
        System.out.printf("Banco:   \t%s\n", this.nomeBanco);
        System.out.printf("Saldo:   \t%f\n\n", this.saldo);
    }

    public ContaCorrente(int numeroConta, String nomeBanco, String nomeCliente) {
        this.numeroConta = numeroConta;
        this.nomeBanco = nomeBanco;
        this.nomeCliente = nomeCliente;
        this.saldo = 0.0;
    }

}
