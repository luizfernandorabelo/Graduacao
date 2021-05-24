public class Main {

    public static void main(String[] args) {

        Senha senha = new Senha(0, 100);

        System.out.println("Tente advinhar a senha");
        int totalTentativas = senha.advinhar();

        System.out.println("Você acertou a senha aleatória depois de " + totalTentativas + " tentativas!");

    }

}
