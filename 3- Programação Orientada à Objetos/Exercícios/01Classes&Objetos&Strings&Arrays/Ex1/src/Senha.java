public class Senha {

    private int minimo;
    private int maximo;
    private int aleatorio;

    public Senha(int minimo, int maximo) {

        Random r = new Random();

        this.minimo = minimo;
        this.maximo = maximo;
        this.aleatorio = r.getIntRand(maximo-minimo) + minimo + 1;
    }

    public int advinhar() {

        int totalTentativas = 0;

        while (true) {
            int chute = EntradaPadrao.leInteiro("Digite um inteiro: ");
            totalTentativas += 1;
            if (chute == aleatorio)
                break;
            System.out.println("Erou!");
        }

        return totalTentativas;
    }

}
