public class Main {

    public static void main(String[] args) {

        PessoaFisica p1 = new PessoaFisica("Neymar", "Paris", "12345678900");
        PessoaFisica p2 = new PessoaFisica("Delamaro", "Sanca", "98765432100");
        PessoaFisica p3 = new PessoaFisica("Rabelo", "SSP", "11122233300");
        PessoaFisica p4 = new PessoaFisica("Gil", "Recife", "99988877700");

        Agenda minhaAgenda = new Agenda(4);

        minhaAgenda.inserePessoa(p1);
        minhaAgenda.inserePessoa(p2);
        minhaAgenda.inserePessoa(p3);
        minhaAgenda.inserePessoa(p4);

        System.out.printf("%d Pessoas na agenda:\n\n", minhaAgenda.getTotalPessoas());
        minhaAgenda.print();

        System.out.println("Usuário de cpf 11122233300: " + minhaAgenda.buscaPessoa("11122233300").getNome());
    }

}
