public class Main {

    public static void main(String[] args) {

        int limiteInferior = EntradaPadrao.leInteiro("Digite o limite inferior: ");
        int limiteSuperior = EntradaPadrao.leInteiro("Digite o limite superior: ");

        Senha senha = new Senha(limiteInferior, limiteSuperior);

        System.out.println("Agora tente advinhar a senha");
        int totalTentativas = senha.advinhar();

        System.out.println("Você acertou a senha aleatória depois de " + totalTentativas + " tentativas!");

    }

}
