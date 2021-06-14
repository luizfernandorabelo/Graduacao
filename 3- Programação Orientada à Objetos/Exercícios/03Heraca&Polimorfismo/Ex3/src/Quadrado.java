public class Quadrado extends Figura {

    private double lado;

    public Quadrado(double lado) throws IllegalArgumentException {
        if (lado <= 0)
            throw new IllegalArgumentException("O lado de um quadrado não pode ser menor ou igual a zero");
        this.lado = lado;
        this.cor = "transparente";
        this.preenchida = false;
    }

    public Quadrado(double lado, String cor, boolean preenchido) throws IllegalArgumentException {
        if (lado <= 0)
            throw new IllegalArgumentException("O lado de um quadrado não pode ser menor ou igual a zero");
        this.lado = lado;
        this.cor = cor;
        this.preenchida = preenchido;
    }

    public double calcularArea() {
        return Math.pow(lado, 2.0);
    }

    public double calcularPerimetro() {
        return 4 * lado;
    }

    public double getLado() {
        return lado;
    }

    public void setLado(double lado) {
        this.lado = lado;
    }

    @Override
    public String toString() {
        String stringRetorno = "Quadrado de lado " + String.format("%.2f", lado);
        if (cor.equals("transparente"))
            stringRetorno += " " + cor;
        else if (preenchida)
            stringRetorno += " preenchido com " + cor;
        else
            stringRetorno += " com contorno " + cor;
        return stringRetorno;
    }

}
