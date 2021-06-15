public class Main {

    public static void main(String[] args) {

        // Criação de algumas pessoas físicas:
        PessoaFisica luiz = new PessoaFisica("Luiz Rabelo", "São Sebastião do Paraíso, Minas Gerais, Brasil",
                "luizfernando2002@hotmai.com", "333.222.111-00", "25/03/2002", "solteiro");
        PessoaFisica dela = new PessoaFisica("Márcio Delamaro", "São Carlos, São Paulo, Brasil",
                "delamaro@icmc.usp.br", "123.456.789-10", "01/01/1965", "casado");
        PessoaFisica einstein = new PessoaFisica("Alberto Einstein", "Ulm, Baden-Wurttemberg, Alemanha",
                "relatividade@mecanica.quantica", "111.222.333-44", "14/03/1879", "solteiro");

        // Criação de algumas pessoas jurídicas:
        PessoaJuridica marinho = new PessoaJuridica("Irineu Marinho", "Niterói, Rio de Janeiro, Brasil",
                "irineu@globo.tv", "99.777.555/0001-33", "112233445", "Rede Globo");
        PessoaJuridica nilce = new PessoaJuridica("Nilce Moretto", "Vancouver, Colúmbia Britânica, Canadá",
                "nilmoretto@cac.youtube", "12.345.678/0001-11", "123456789", "Cadê a Chave");
        PessoaJuridica neymar = new PessoaJuridica("Neymar Júnior", "Paris, Paris, França",
                "neymar@junior.fr", "22.333.444/0001-55", "667788990", "Instituto Neymar Jr");

        // Adição das pessoas na agenda:
        Agenda.adicionarPessoa(luiz);
        Agenda.adicionarPessoa(dela);
        Agenda.adicionarPessoa(einstein);
        Agenda.adicionarPessoa(marinho);
        Agenda.adicionarPessoa(nilce);
        Agenda.adicionarPessoa(neymar);

        // Impressão inicial da agenda:
        System.out.println("\n>>> Agenda com os nomes iniciais:");
        Agenda.imprimir();

        // Busca por cpf:
        PessoaFisica pfBuscada = (PessoaFisica) Agenda.buscarPessoa("123.456.789-10");
        System.out.println("\n>>> O dono do cpf 123.456.789-10 é " + pfBuscada.getNome());

        // Busca por cnpj:
        PessoaJuridica pjBuscada = (PessoaJuridica) Agenda.buscarPessoa("99.777.555/0001-33");
        System.out.println("\n>>> O dono do cnpj 99.777.555/0001-33 é " + pjBuscada.getNome());

        // Busca por nome:
        Pessoa pBuscada = Agenda.buscarPessoaPorNome("Nilce Moretto");
        System.out.println("\n>>> O email de Nilce Moretto é " + pBuscada.getEmail());

        // Ordenação da agenda:
        Agenda.ordenar();
        System.out.println("\n>>> Agenda ordenada:");
        Agenda.imprimir();

        // Remoção de 2 pessoas físicas:
        Agenda.removerPessoa("111.222.333-44");
        Agenda.removerPessoa("333.222.111-00");
        System.out.println("\n>>> Agenda após remover Einstein e Luiz:");
        Agenda.imprimir();

        // Remoção de 1 pessoa jurídica:
        Agenda.removerPessoa("22.333.444/0001-55");
        System.out.println("\n>>> Agenda após remover Neymar:");
        Agenda.imprimir();

    }

}
