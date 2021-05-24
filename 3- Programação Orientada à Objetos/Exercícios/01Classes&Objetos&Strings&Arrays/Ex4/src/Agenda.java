public class Agenda {

    private int tamanhoAgenda;
    private PessoaFisica[] pessoas;
    private int totalPessoas;

    public void inserePessoa(PessoaFisica novaPessoa) {
        if(totalPessoas >= tamanhoAgenda)
            return;
        pessoas[totalPessoas++] = novaPessoa;
    }

    public PessoaFisica buscaPessoa(String cpf) {
        for (PessoaFisica pessoaAtual: pessoas)
            if (pessoaAtual.getCpf().equals(cpf))
                return pessoaAtual;
        return null;
    }

    public void print() {
        for (PessoaFisica pessoaAtual: pessoas)
            pessoaAtual.print();
    }

    public int getTotalPessoas() {
        return totalPessoas;
    }

    public Agenda(int tamanhoAgenda) {
        this.tamanhoAgenda = tamanhoAgenda > 0 ? tamanhoAgenda : 0;
        this.pessoas = new PessoaFisica[tamanhoAgenda];
        this.totalPessoas = 0;
    }

}
