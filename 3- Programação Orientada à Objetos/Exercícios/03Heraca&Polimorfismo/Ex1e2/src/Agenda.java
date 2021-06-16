import java.util.Arrays;

/* NOTA: Dividi logicamente o array de pessoas em 2 regiões: sendo a primeira das pessoas físicas e a segunda das jurídicas.
         Isso trouxe a desvantagem da possibilidade de ter que fazer eventuais shifts na inserção de pessoas físicas.
         Mas também trouxe a vantagem de deixar o arranjo já pronto para a função de ordenação que será aplicada (quick sort), além de que
         na busca e remoção por cpf ou cnpj, são comparadas apenas as pessoas correspondentes à categoria do documento passado por parâmetro.
 */

public class Agenda {

    private static int capacidade = 1; // quantidade de pessoas que a agenda é capaz de armazenar
    private static int totalPessoasFisicas = 0; // quantidade de pessoas físicas adicionadas na agenda
    private static int totalPessoasJuridicas = 0; // quantidade de pessoas jurídicas adicionadas na agenda
    private static int totalPessoas = 0; // totalPessoasFisicas + totalPessoasJuridicas
    private static Pessoa[] pessoas = new Pessoa[capacidade]; // arranjo com todas as pessoas inseridas na agenda

    private static void garantirCapacidade() {
        if (totalPessoas == capacidade) {
            pessoas = Arrays.copyOf(pessoas, capacidade * 2);
            capacidade *= 2;
        }
    }

    private static void adicionarPessoaFisica(Pessoa pessoa) {

        for (int i = 0; i < totalPessoasJuridicas; i++)
            pessoas[totalPessoas-i] = pessoas[totalPessoas-(i+1)];

        pessoas[totalPessoasFisicas++] = pessoa;
        totalPessoas++;
    }

    private static void adicionarPessoaJuridica(Pessoa pessoa) {
        pessoas[totalPessoas++] = pessoa;
        totalPessoasJuridicas++;
    }

    public static void adicionarPessoa(Pessoa pessoa) {

        garantirCapacidade();

        if (pessoa instanceof PessoaFisica)
            adicionarPessoaFisica(pessoa);
        else
            adicionarPessoaJuridica(pessoa);
    }

    private static void removerPessoaNoIndice(int indice) {
        for (int i = indice; i < totalPessoas - 1; i++) {
            pessoas[i] = pessoas[i+1];
        }
        pessoas[totalPessoas-1] = null;
        totalPessoas--;
    }

    private static void removerPessoaFisica(String cpf) {
        for (int i = 0; i < totalPessoasFisicas; i++) {
            PessoaFisica pessoaAtual = (PessoaFisica) pessoas[i];
            if (pessoaAtual.getCpf().equals(cpf)) {
                removerPessoaNoIndice(i);
                totalPessoasFisicas--;
                break;
            }
        }
    }

    private static void removerPessoaJuridica(String cnpj) {
        for (int i = totalPessoasFisicas; i < totalPessoas; i++) {
            PessoaJuridica pessoaAtual = (PessoaJuridica) pessoas[i];
            if (pessoaAtual.getCnpj().equals(cnpj)) {
                removerPessoaNoIndice(i);
                totalPessoasJuridicas--;
                break;
            }
        }
    }

    public static void removerPessoa(String documento) {
        if (documento.length() == PessoaFisica.TAM_CPF)
            removerPessoaFisica(documento);
        else
            removerPessoaJuridica(documento);
    }

    private static Pessoa buscarPessoaFisica(String cpf) {
        for (int i = 0; i < totalPessoasFisicas; i++) {
            PessoaFisica pessoaAtual = (PessoaFisica) pessoas[i];
            if (pessoaAtual.getCpf().equals(cpf))
                return pessoas[i];
        }
        return null;
    }

    private static Pessoa buscarPessoaJuridica(String cnpj) {
        for (int i = totalPessoasFisicas; i < totalPessoas; i++) {
            PessoaJuridica pessoaAtual = (PessoaJuridica) pessoas[i];
            if (pessoaAtual.getCnpj().equals(cnpj))
                return pessoas[i];
        }
        return null;
    }

    public static Pessoa buscarPessoa(String documento) {
        if (documento.length() == PessoaFisica.TAM_CPF)
            return buscarPessoaFisica(documento);
        else
            return buscarPessoaJuridica(documento);
    }

    public static Pessoa buscarPessoaPorNome(String nome) {
        for (Pessoa pessoaAtual : pessoas) {
            if (pessoaAtual.getNome().equals(nome))
                return pessoaAtual;
        }
        return null;
    }

    public static void imprimir() {

        System.out.println("-> " + totalPessoasFisicas + " Pessoas Físicas:");
        for (int i = 0; i < totalPessoasFisicas; i++) {
            PessoaFisica pessoaAtual = (PessoaFisica) pessoas[i];
            System.out.println("   * " + pessoaAtual);
        }

        System.out.println("-> " + totalPessoasJuridicas + " Pessoas Jurídicas:");
        for (int i = totalPessoasFisicas; i < totalPessoas; i++) {
            PessoaJuridica pessoaAtual = (PessoaJuridica) pessoas[i];
            System.out.println("   * " + pessoaAtual);
        }
    }

    private static void trocarPessoas(int indice1, int indice2) {
        Pessoa aux = pessoas[indice1];
        pessoas[indice1] = pessoas[indice2];
        pessoas[indice2] = aux;
    }

    private static int particaoFisicas(int inicio, int fim) {

        String cpfPivo = ((PessoaFisica) pessoas[fim]).getCpf();
        int i = inicio - 1; // índice final do pivô

        for (int j = inicio; j <= fim; j++) {
            String cpfAtual = ((PessoaFisica) pessoas[j]).getCpf();
            if (cpfAtual.compareTo(cpfPivo) <= 0) {
                i++;
                trocarPessoas(i, j);
            }
        }

        return i;
    }

    private static int particaoJuridicas(int inicio, int fim) {

        String cnpjPivo = ((PessoaJuridica) pessoas[fim]).getCnpj();
        int i = inicio - 1; // índice final do pivô

        for (int j = inicio; j <= fim; j++) {
            String cnpjAtual = ((PessoaJuridica) pessoas[j]).getCnpj();
            if (cnpjAtual.compareTo(cnpjPivo) <= 0) {
                i++;
                trocarPessoas(i, j);
            }
        }

        return i;
    }

    private static void ordenarPessoasFisicas(int inicio, int fim) {

        if (inicio >= fim)
            return;

        int indicePivo = particaoFisicas(inicio, fim);

        ordenarPessoasFisicas(inicio, indicePivo-1);
        ordenarPessoasFisicas(indicePivo, fim);
    }

    private static void ordenarPessoasJuridicas(int inicio, int fim) {

        if (inicio >= fim)
            return;

        int indicePivo = particaoJuridicas(inicio, fim);

        ordenarPessoasJuridicas(inicio, indicePivo-1);
        ordenarPessoasJuridicas(indicePivo, fim);
    }

    public static void ordenar() {
        ordenarPessoasFisicas(0, totalPessoasFisicas-1);
        ordenarPessoasJuridicas(totalPessoasFisicas, totalPessoas-1);
    }

}
