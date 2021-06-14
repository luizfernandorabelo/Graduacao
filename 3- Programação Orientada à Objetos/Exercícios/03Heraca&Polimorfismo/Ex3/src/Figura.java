public abstract class Figura {

    protected String cor;
    protected boolean preenchida;

    public abstract double calcularArea();
    public abstract double calcularPerimetro();

    public String getCor() {
        return cor;
    }

    public boolean ehPreenchida() {
        return preenchida;
    }
}
