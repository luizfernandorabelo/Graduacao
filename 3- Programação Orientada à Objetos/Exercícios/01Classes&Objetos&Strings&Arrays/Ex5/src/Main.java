public class Main {

    public static void main(String[] args) {

        ContaCorrente conta1 = new ContaCorrente(0, "Itau", "Filho");
        ContaCorrente conta2 = new ContaCorrente(1, "Bradesco", "Mae");
        ContaCorrente conta3 = new ContaCorrente(2, "Sicoob", "Pai");

        conta1.depositar(100);
        conta2.depositar(700);
        conta3.depositar(600);
        // Saldos: 100, 700, 600

        conta1.sacar(10);
        conta2.sacar(100);
        conta3.sacar(200);
        // Saldos: 90, 600, 400

        conta2.transferir(conta3, 150);
        // Saldos: 90, 450, 550;

        conta3.transferir(conta1, 200);
        // Saldos: 290, 450, 350;

        conta1.print();
        conta2.print();
        conta3.print();

    }

}
