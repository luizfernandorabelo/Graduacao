public class RolaDados {

    private int totalDados;
    private Dado[] arrayDados;

    public int[] rolar() {

        int[] valoresDados = new int[totalDados];

        for (int i = 0; i < totalDados; i++) {
            Dado dadoAtual = arrayDados[i];
            valoresDados[i] = dadoAtual.rolar();
        }

        return valoresDados;
    }

    public int[] rolar(boolean[] quais) {

        int[] valoresDados = new int[totalDados];

        for (int i = 0; i < totalDados; i++) {
            Dado dadoAtual = arrayDados[i];
            valoresDados[i] = quais[i] == true ? dadoAtual.rolar() : dadoAtual.getLado();
        }

        return valoresDados;
    }

    public int[] rolar(String s) {

        boolean[] quais = new boolean[totalDados];

        for (int i = 0; i < totalDados; i++)
            quais[i] = false;

        String[] indices = s.split(" ");

        for (String stringAtual: indices) {
            int indiceDado = Character.getNumericValue(stringAtual.charAt(0)) - 1;
            if (indiceDado >= 0 && indiceDado < totalDados)
                quais[indiceDado] = true;
        }

        return rolar(quais);
    }

    @Override public String toString() {

        String[][] representacaoDados = new String[totalDados][5];

        for (int i = 0; i < totalDados; i++) {
            Dado dadoAtual = arrayDados[i];
            representacaoDados[i] = dadoAtual.toString().split("\n");
        }

        String stringRetorno = new String();

        for (int i = 0; i < totalDados; i++)
            stringRetorno += (i+1) + "      \t";
        stringRetorno += "\n";

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < totalDados; j++)
                stringRetorno += representacaoDados[j][i] + "\t";
            stringRetorno += "\n";
        }

        return stringRetorno;
    }

    public RolaDados(int n) {

        totalDados = n > 0 ? n : 0;
        arrayDados = new Dado[totalDados];

        for (int i = 0; i < n; i++) {
            arrayDados[i] = new Dado();
            try {
                Thread.sleep(n);
            } catch (Exception e) {
                System.err.println("Erro");
            }
        }
    }

}
