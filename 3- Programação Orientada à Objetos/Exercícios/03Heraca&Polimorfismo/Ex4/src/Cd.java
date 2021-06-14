public class Cd extends Produto {

    private String album;
    private String banda;

    public Cd(long codigo, String album, String banda) {
        super(codigo, album + " - " + banda, "CD   ");
        this.album = album;
        this.banda = banda;
    }

    public String getAlbum() {
        return album;
    }

    public String getBanda() {
        return banda;
    }

}
