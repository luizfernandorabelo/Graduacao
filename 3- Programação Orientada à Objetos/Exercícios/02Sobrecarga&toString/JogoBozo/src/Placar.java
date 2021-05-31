public class Placar {

    private static int[] valoresTabuleiro = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    private static int score = 0;

    private static final int POSICAO_UM = 1;
    private static final int POSICAO_DOIS = 2;
    private static final int POSICAO_TRES = 3;
    private static final int POSICAO_QUATRO = 4;
    private static final int POSICAO_CINCO = 5;
    private static final int POSICAO_SEIS = 6;
    private static final int POSICAO_FULL_HAND = 7;
    private static final int POSICAO_SEQUENCIA = 8;
    private static final int POSICAO_QUADRA = 9;
    private static final int POSICAO_QUINA = 10;

    private int[] obterOcorrenciasDosValoresDados(int[] valoresDados) {

        int[] ocorrencias = new int[6];

        for (int i = 0; i < valoresDados.length; i++)
            ocorrencias[ valoresDados[i] - 1 ] += 1;

        return ocorrencias;
    }

    private boolean fullHandEhValido(int[] valoresDados) {

        boolean duplaEncontrada = false;
        boolean triplaEncontrada = false;

        int[] vetorOcorrencias = obterOcorrenciasDosValoresDados(valoresDados);

        for (int ocorrenciaAtual : vetorOcorrencias) {
            if (ocorrenciaAtual == 2)
                duplaEncontrada = true;
            if (ocorrenciaAtual == 3)
                triplaEncontrada = true;
            if (duplaEncontrada && triplaEncontrada)
                return true;
        }

        return quadraEhValida(valoresDados) || quinaEhValida(valoresDados);
    }

    private boolean quadraEhValida(int[] valoresDados) {

        int[] vetorOcorrencias = obterOcorrenciasDosValoresDados(valoresDados);

        for (int ocorrenciaAtual : vetorOcorrencias) {
            if (ocorrenciaAtual >= 4)
                return true;
        }

        return false;
    }

    private boolean quinaEhValida(int[] valoresDados) {

        int[] vetorOcorrencias = obterOcorrenciasDosValoresDados(valoresDados);

        for (int ocorrenciaAtual : vetorOcorrencias) {
            if (ocorrenciaAtual >= 5)
                return true;
        }

        return false;
    }

    private boolean sequenciaEhValida(int[] valoresDados) {

        int[] vetorOcorrencias = obterOcorrenciasDosValoresDados(valoresDados);

        for (int ocorrenciaAtual : vetorOcorrencias) {
            if (ocorrenciaAtual > 1)
                return false;
        }

        return true;
    }

    private void addLateral(int posicao, int[] valoresDados) {

        int totalDadosValidos = 0;

        for (int i = 0; i < valoresDados.length; i++) {
            if (valoresDados[i] == posicao)
                totalDadosValidos++;
        }

        valoresTabuleiro[posicao-1] = totalDadosValidos * posicao;
        score += valoresTabuleiro[posicao-1];
    }

    private void addFullHand(int[] valoresDados) {
        if (fullHandEhValido(valoresDados)) {
            valoresTabuleiro[POSICAO_FULL_HAND-1] = 15;
            score += 15;
        }
        else
            valoresTabuleiro[POSICAO_FULL_HAND-1] = 0;
    }

    private void addSequencia(int[] valoresDados) {
        if (sequenciaEhValida(valoresDados)) {
            valoresTabuleiro[POSICAO_SEQUENCIA-1] = 20;
            score += 20;
        }
        else
            valoresTabuleiro[POSICAO_SEQUENCIA-1] = 0;
    }

    private void addQuadra(int[] valoresDados) {
        if (quadraEhValida(valoresDados)) {
            valoresTabuleiro[POSICAO_QUADRA-1] = 30;
            score += 30;
        }
        else
            valoresTabuleiro[POSICAO_QUADRA-1] = 0;
    }

    private void addQuina(int[] valoresDados) {
        if (quinaEhValida(valoresDados)) {
            valoresTabuleiro[POSICAO_QUINA-1] = 40;
            score += 40;
        }
        else
            valoresTabuleiro[POSICAO_QUINA-1] = 0;
    }

    public void add(int posicao, int[] valoresDados) throws java.lang.IllegalArgumentException {

        if (posicao < POSICAO_UM || posicao > POSICAO_QUINA || valoresTabuleiro[posicao-1] != -1)
                throw new IllegalArgumentException();

        switch (posicao) {
            case POSICAO_UM:
                addLateral(POSICAO_UM, valoresDados);
                break;
            case POSICAO_DOIS:
                addLateral(POSICAO_DOIS, valoresDados);
                break;
            case POSICAO_TRES:
                addLateral(POSICAO_TRES, valoresDados);
                break;
            case POSICAO_QUATRO:
                addLateral(POSICAO_QUATRO, valoresDados);
                break;
            case POSICAO_CINCO:
                addLateral(POSICAO_CINCO, valoresDados);
                break;
            case POSICAO_SEIS:
                addLateral(POSICAO_SEIS, valoresDados);
                break;
            case POSICAO_FULL_HAND:
                addFullHand(valoresDados);
                break;
            case POSICAO_SEQUENCIA:
                addSequencia(valoresDados);
                break;
            case POSICAO_QUADRA:
                addQuadra(valoresDados);
                break;
            case POSICAO_QUINA:
               addQuina(valoresDados);
               break;
            default:
                break;
        }
    }

    public int getScore() {
        return score;
    }

    private String posicaoTabuleiroToString(int indice) {
        return (
            valoresTabuleiro[indice] == -1 ?
                    "(" + (indice + 1) + ")" :
                    String.format("%03d", valoresTabuleiro[indice])
        );
    }

    @Override public String toString() {

        String stringRetorno = "";

        for (int i = 0; i < 3; i++) {
            stringRetorno += posicaoTabuleiroToString(i) + "    |";
            stringRetorno += "  " + posicaoTabuleiroToString(i+6) + "  |";
            stringRetorno += "    " + posicaoTabuleiroToString(i+3) + "\n";
            stringRetorno += "-----------------------\n";
        }
        stringRetorno += " |       " + posicaoTabuleiroToString(9) + "       |\n";

        return stringRetorno;
    }
}