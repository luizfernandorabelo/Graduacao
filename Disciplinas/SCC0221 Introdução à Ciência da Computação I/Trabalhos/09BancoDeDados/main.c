#include "myUsefulFunctions.h"

int main(int argc, char *argv[]){
    
    //Carregamento dos Metadados para a Memória:
    metadata *registerFields = loadRegisterFields();
    
    //Interface com o Usuário:
    readCommands(&registerFields);
    
    //Liberação de Memória Alocada:
    unloadRegisterFields(registerFields);

    return 0;
}

