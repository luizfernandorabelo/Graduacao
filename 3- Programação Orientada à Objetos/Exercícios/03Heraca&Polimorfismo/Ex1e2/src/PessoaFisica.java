public class PessoaFisica extends Pessoa {

    private String cpf;
    private String dataNascimento; // DD-MM-AAAA
    private String estadoCivil;

    public static final int TAM_CPF = 14;

    public PessoaFisica(String nome, String endereco, String email, String cpf, String dataNascimento, String estadoCivil) {
        super(nome, endereco, email);
        this.cpf = cpf;
        this.dataNascimento = dataNascimento;
        this.estadoCivil = estadoCivil;
    }

    public String getCpf() {
        return cpf;
    }

    public String getDataNascimento() {
        return dataNascimento;
    }

    public String getEstadoCivil() {
        return estadoCivil;
    }

    public void setEstadoCivil(String estadoCivil) {
        this.estadoCivil = estadoCivil;
    }

    @Override
    public String toString() {
        return cpf + " " + nome;
    }

}
