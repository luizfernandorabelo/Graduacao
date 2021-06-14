public class Livro extends Produto {

    private String titulo;
    private String autor;

    public Livro(long codigo, String autor, String titulo) {
        super(codigo, titulo + " - " + autor, "LIVRO");
        this.titulo = titulo;
        this.autor = autor;
    }

    public String getTitulo() {
        return titulo;
    }

    public String getAutor() {
        return autor;
    }

}
