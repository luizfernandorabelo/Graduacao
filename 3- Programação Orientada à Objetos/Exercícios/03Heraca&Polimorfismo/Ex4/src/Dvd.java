public class Dvd extends Produto {

    public String titulo;
    public String estudio;

    public Dvd(long codigo, String titulo, String estudio) {
        super(codigo, titulo + " - " + estudio, "DVD  ");
        this.titulo = titulo;
        this.estudio = estudio;
    }

    public String getTitulo() {
        return titulo;
    }

    public String getEstudio() {
        return estudio;
    }

}
