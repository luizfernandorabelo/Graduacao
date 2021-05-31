    public class Bozo {

    private static String leStringEntrada(String label) {

        System.out.print(label);
        String stringEntrada = "";

        try {
            stringEntrada = EntradaTeclado.leString();
        } catch (Exception e) {
            System.out.println("Erro na leitura de string!");
            return "";
        }

        return stringEntrada;
    }

    private static int leIntEntrada(String label) {

        boolean entradaValida = false;
        int intEntrada = 0;

        while (!entradaValida) {
            try {
                System.out.print(label);
                intEntrada = EntradaTeclado.leInt();
                entradaValida = true;
            } catch (Exception e) {
                System.err.println("Valor inválido!");
                entradaValida = false;
            }
        }

        return intEntrada;
    }

    private static void adicionaPontuacaoPlacar(Placar placar, int[] valoresDados) {

        boolean insercaoValida = false;
        int posicao = 0;

        while (!insercaoValida) {
            posicao = leIntEntrada("Digite a posição que você quer ocupar: ");
            try {
                placar.add(posicao, valoresDados);
                insercaoValida = true;
            } catch (IllegalArgumentException e) {
                System.out.println("Essa posição não existe ou já está ocupada!");
                insercaoValida = false;
            }
        }
    }

    public static void main(String[] args) {

        final int TOTAL_JOGADAS = 10;
        int jogadaAtual = 1;

        RolaDados dados = new RolaDados(5);
        Placar placar = new Placar();

        while (jogadaAtual <= TOTAL_JOGADAS) {

            System.out.println("\n" + placar);

            System.out.println("***** Jogada " + jogadaAtual + " *****");
            leStringEntrada("Digite ENTER para lançar os dados" + "\n");

            int[] valoresDados = dados.rolar();
            System.out.println(dados);

            for (int i = 0; i < 2; i++) {
                String reRolados = leStringEntrada("Digite os dados que você quer trocar (separados por espaço): ");
                if (reRolados.length() == 0) {
                    System.out.println();
                    break;
                }
                valoresDados = dados.rolar(reRolados);
                System.out.println(dados);
            }

            System.out.println(placar);
            adicionaPontuacaoPlacar(placar, valoresDados);

            jogadaAtual++;
        }

        System.out.println(placar);
        System.out.println("Fim do jogo! Seu score final é de " + placar.getScore());
    }
}
