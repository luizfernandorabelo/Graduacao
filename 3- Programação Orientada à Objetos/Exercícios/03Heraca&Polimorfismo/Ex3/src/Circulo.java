public class Circulo extends Figura {

    private double raio;
    private static final double PI = 3.14159;

    public Circulo(double raio) throws IllegalArgumentException {
        if (raio <= 0) {
            throw new IllegalArgumentException("O raio não pode ser menor ou igual a zero!");
        }
        this.raio = raio;
        this.cor = "transparente";
        this.preenchida = false;
    }

    public Circulo(double raio, String cor, boolean preenchido) throws IllegalArgumentException {
        if (raio <= 0) {
            throw new IllegalArgumentException("O raio não pode ser menor ou igual a zero!");
        }
        this.raio = raio;
        this.cor = cor;
        this.preenchida = preenchido;
    }

    public double calcularArea() {
        return PI * Math.pow(raio, 2.0);
    }

    public double calcularPerimetro() {
        return  2 * PI * raio;
    }

    public double getRaio() {
        return raio;
    }

    public void setRaio(double raio) {
        this.raio = raio;
    }

    @Override
    public String toString() {
        String stringRetorno = "Círculo de raio " + String.format("%.2f", raio);
        if (cor.equals("transparente"))
            stringRetorno += " " + cor;
        else if (preenchida)
            stringRetorno += " preenchido com " + cor;
        else
            stringRetorno += " com contorno " + cor;
        return stringRetorno;
    }

}
