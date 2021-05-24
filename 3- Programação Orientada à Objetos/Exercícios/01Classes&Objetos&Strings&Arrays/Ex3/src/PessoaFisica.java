public class PessoaFisica {

    private String nome;
    private String endereco;
    private String cpf;

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setEndereco(String endereco) {
        this.endereco = endereco;
    }

    public void setCpf(String cpf) {
        this.cpf = cpf;
    }

    public String getNome() {
        return nome;
    }

    public String getEndereco() {
        return endereco;
    }

    public String getCpf() {
        return cpf;
    }

    public void print() {
        System.out.printf("NOME:    \t%s\n", nome);
        System.out.printf("ENDEREÇO:\t%s\n", endereco);
        System.out.printf("CPF:     \t%s\n\n", cpf);
    }

    public PessoaFisica() {
        nome = "";
        endereco = "";
        cpf = "";
    }

    public PessoaFisica(String nome, String endereco, String cpf) {
        this.nome = nome;
        this.endereco = endereco;
        this.cpf = cpf;
    }

}
