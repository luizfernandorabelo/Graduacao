public class Dado {

    private int numeroLados;
    private int ladoDeCima;
    private Random r = new Random();

    public int getLado() {
        return ladoDeCima;
    }

    public int rolar() {
        ladoDeCima = r.getIntRand(numeroLados) + 1;
        return getLado();
    }

    @Override
    public String toString() {
        String stringRetorno = "+-----+\n";
        switch (ladoDeCima) {
            case 1:
                stringRetorno += "|     |\n";
                stringRetorno += "|  *  |\n";
                stringRetorno += "|     |\n";
                break;
            case 2:
                stringRetorno += "|*    |\n";
                stringRetorno += "|     |\n";
                stringRetorno += "|    *|\n";
                break;
            case 3:
                stringRetorno += "|*    |\n";
                stringRetorno += "|  *  |\n";
                stringRetorno += "|    *|\n";
                break;
            case 4:
                stringRetorno += "|*   *|\n";
                stringRetorno += "|     |\n";
                stringRetorno += "|*   *|\n";
                break;
            case 5:
                stringRetorno += "|*   *|\n";
                stringRetorno += "|  *  |\n";
                stringRetorno += "|*   *|\n";
                break;
            case 6:
                stringRetorno += "|* * *|\n";
                stringRetorno += "|     |\n";
                stringRetorno += "|* * *|\n";
                break;
            default:
                return "A função toString tem suporte para representar dados apenas de 1 a 6 lados\n";
        }
        stringRetorno += "+-----+\n";
        return stringRetorno;
    }

    public Dado() {
        numeroLados = 6;
        ladoDeCima = 1;
    }

    public Dado(int numeroLados) {
        numeroLados = numeroLados > 0 ? numeroLados : 0;
        ladoDeCima = 1;
    }

}
