public class Retangulo extends Figura {

    private double base;
    private double altura;

    public Retangulo(double base, double altura) throws IllegalArgumentException {
        if (base <= 0 || altura <= 0)
            throw new IllegalArgumentException("As dimensões de um retângulo não podem ser menores ou iguais a zero!");
        this.base = base;
        this.altura = altura;
        this.cor = "transparente";
        this.preenchida = false;
    }

    public Retangulo(double base, double altura, String cor, boolean preenchido) throws IllegalArgumentException {
        if (base <= 0 || altura <= 0)
            throw new IllegalArgumentException("As dimensões de um retângulo não podem ser menores ou iguais a zero!");
        this.base = base;
        this.altura = altura;
        this.cor = cor;
        this.preenchida = preenchido;
    }

    public double calcularArea() {
        return base * altura;
    }

    public double calcularPerimetro() {
        return 2 * (base + altura);
    }

    public double getBase() {
        return base;
    }

    public double getAltura() {
        return altura;
    }

    public void setBase(double base) {
        this.base = base;
    }

    public void setAltura(double altura) {
        this.altura = altura;
    }

    @Override
    public String toString() {
        String stringRetorno = "Retângulo de base " + String.format("%.2f", base) +
                               " e altura " + String.format("%.2f", altura);
        if (cor.equals("transparente"))
            stringRetorno += " " + cor;
        else if (preenchida)
            stringRetorno += "preenchido com " + cor;
        else
            stringRetorno += "com contorno " + cor;
        return stringRetorno;
    }

}
