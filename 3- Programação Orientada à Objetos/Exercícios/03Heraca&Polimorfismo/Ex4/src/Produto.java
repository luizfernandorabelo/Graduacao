public class Produto {

    protected long codigo;
    protected String nome;
    protected String categoria;

    public Produto(long codigo, String nome, String categoria) {
        this.codigo = codigo;
        this.nome = nome;
        this.categoria = categoria;
    }

    public long getCodigo() {
        return codigo;
    }

    public String getNome() {
        return nome;
    }

    public String getCategoria() {
        return categoria;
    }

}
