public class Main {

    public static void main(String[] args) {

        PessoaFisica p1 = new PessoaFisica();
        p1.setNome("Neymar da Silva Santos Júnior");
        p1.setEndereco("Paris, França");
        p1.setCpf("12345678900");

        PessoaFisica p2 = new PessoaFisica("Márcio Eduardo Delamaro",
                                           "São Carlos, Brazil",
                                           "98765432100");

        System.out.println("Pessoa 1:");
        p1.print();

        System.out.println("Pessoa 2:");
        p2.print();
    }

}
