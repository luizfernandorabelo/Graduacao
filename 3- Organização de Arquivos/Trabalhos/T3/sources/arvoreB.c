// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include "arvoreB.h"

/*
Descrição: Aloca espaço na memória para uma estrutura do tipo RegistroDadosAB, 
inicializando o campo byteOffset com VALOR_NULO (-1) 
@param chave: chave que será preenchida no campo chave da estrutura alocada
@return um ponteiro para a região de memória em que o registro de dados foi alocado
*/
RegistroDadosAB *alocaRegistroDadosAB(int chave) {

    RegistroDadosAB *registroDados = malloc(sizeof(RegistroDadosAB));

    registroDados->chave = chave;
    registroDados->byteOffset = VALOR_NULO;

    return registroDados;
}

/*
Descrição: Aloca espaço na memória para um vetor de ponteiros para estruturas do tipo RegistroDadosAB, 
inicializando os campos de cada registro de dados com valores nulos pela função alocaRegistroDadosAB
@param nroRegistros: tamanho do vetor a ser alocado
@return um ponteiro para a região de memória em que o vetor foi alocado
*/
RegistroDadosAB **alocaVetorRegistroDadosAB(int nroRegistros) {

    RegistroDadosAB **vetor = malloc(nroRegistros * sizeof(RegistroDadosAB *));

    for (int i = 0; i < nroRegistros; i++)
        vetor[i] = alocaRegistroDadosAB(VALOR_NULO);
    
    return vetor;
}

/*
Descrição: Libera a memória alocada para um vetor de ponteiros para estruturas do tipo RegistroDadosAB
@param vetor: vetor a ser liberado
@param nroRegistros: número de ponteiros presentes no vetor
*/
void liberaVetorRegistroDadosAB(RegistroDadosAB **vetor, int nroRegistros) {
    for (int i = 0; i < nroRegistros; i++)
        free(vetor[i]);
    free(vetor);
}

/*
Descrição: Aloca espaço na memória para uma estrutura do tipo NoDadosAB, 
inicializando os campos folha com '1' (verdadeiro), nroChavesIndexadas com 0,  
RRNdoNo com VALOR_NULO (-1), registros com ponteiros preenchidos pela função 
alocaRegistoDados e filhos com VALOR_NULO
@return Um ponteiro para a região de memória em que o no de dados foi alocado
*/
NoDadosAB *alocaNoDadosAB(void) {

    NoDadosAB *noDados = malloc(sizeof(NoDadosAB));

    noDados->folha = '1';
    noDados->nroChavesIndexadas = 0;
    noDados->RRNdoNo = VALOR_NULO;

    for (int i = 0; i < ORDEM_ARVORE - 1; i++)
        noDados->registros[i] = alocaRegistroDadosAB(VALOR_NULO);

    memset(noDados->filhos, VALOR_NULO, (ORDEM_ARVORE * sizeof(int)));

    return noDados;
}

/*
Descrição: Libera a memória alocada por um nó de dados da árvore B
@param noDados: nó de dados a ser liberado
*/
void liberaNoDadosAB(NoDadosAB *noDados) {
    for (int i = 0; i < (ORDEM_ARVORE-1); i++)
        free(noDados->registros[i]);
    free(noDados);
}

/*
Descrição: Aloca espaço na memória para uma estrutura do tipo NoCabecalhoAB, 
inicializando os campos RRNraiz com VALOR_NULO (-1), RRNproxNo com 0, status 
com '0' (arquivo inconsistente) e lixo com 68 bytes '\@' 
@return Um ponteiro para a região de memória em que o no de cabecalho foi alocado
*/
NoCabecalhoAB *alocaNoCabecalhoAB(void) {

    NoCabecalhoAB *noCabecalho = malloc(sizeof(NoCabecalhoAB));

    noCabecalho->RRNraiz = VALOR_NULO;
    noCabecalho->RRNproxNo = 0;
    noCabecalho->status = '0';
    memset(noCabecalho->lixo, '@', 68);

    return noCabecalho;
}

/*
Descrição: Aloca espaço na memória para uma estrutura do tipo RegistroPromovido, 
inicializando todos os seus campos com VALOR_NULO (-1)
@return Um ponteiro para a região de memória em que o a chave promovida foi alocada
*/
RegistroPromovido *alocaRegistroPromovidoAB(void) {

    RegistroPromovido *registroPromovido = malloc(sizeof(RegistroPromovido));

    registroPromovido->chave = VALOR_NULO;
    registroPromovido->byteOffset = VALOR_NULO;
    registroPromovido->RRNfilhoDireita = VALOR_NULO;

    return registroPromovido;
}

/*
Descrição: Verifica se o arquivo passado por parâmetro é vazio
@param arquivoIndice: arquivo de índice que será verificado
@return int 1 se verdadeiro ou 0 se falso
*/
bool arquivoIndiceEhVazio(FILE *arquivoIndice) {

    char byteAtual;
    fread(&byteAtual, 1, 1, arquivoIndice);

    if (feof(arquivoIndice))
        return true;

    fseek(arquivoIndice, -1, SEEK_CUR);
    return false;
}

/*
Descrição: Obtém o nó de cabeçalho de um arquivo de índice
@param arquivoIndice: arquivo de índice do qual o cabeçalho será extraído
@return Um ponteiro para a região de memória em que o cabeçalho foi armazenado 
*/
NoCabecalhoAB *carregaNoCabecalhoDaAB(FILE *arquivoIndice) {

    NoCabecalhoAB *noCabecalho = alocaNoCabecalhoAB();

    fseek(arquivoIndice, 0, SEEK_SET);

    if (!arquivoIndiceEhVazio(arquivoIndice)) {
        fread(&noCabecalho->status, 1, 1, arquivoIndice);
        fread(&noCabecalho->RRNraiz, sizeof(int), 1, arquivoIndice);
        fread(&noCabecalho->RRNproxNo, sizeof(int), 1, arquivoIndice);
    }

    return noCabecalho;
}

/*
Descrição: Obtém um nó de dados de um arquivo de índice a partir de seu RRN
@param arquivoIndice: arquivo de índice do qual o no de dados será extraído
@param rrn: rrn do no de dados no arquivo de índice 
@return Um ponteiro para a região de memória em que o no de dados foi armazenado 
*/
NoDadosAB *carregaNoDadosDaAB(FILE *arquivoIndice, int rrn) {

    NoDadosAB *noDados = alocaNoDadosAB();

    fseek(arquivoIndice, (rrn + 1) * TAM_PAGINA, SEEK_SET); // (rrn + 1) por conta do no de cabeçalho

    fread(&noDados->folha, 1, 1, arquivoIndice);
    fread(&noDados->nroChavesIndexadas, sizeof(int), 1, arquivoIndice);
    fread(&noDados->RRNdoNo, sizeof(int), 1, arquivoIndice);
    fread(&noDados->filhos[0], sizeof(int), 1, arquivoIndice);

    for (int i = 0; i < ORDEM_ARVORE - 1; i++) {
        fread(&noDados->registros[i]->chave, sizeof(int), 1, arquivoIndice);
        fread(&noDados->registros[i]->byteOffset, sizeof(long long), 1, arquivoIndice);
        fread(&noDados->filhos[i+1], sizeof(int), 1, arquivoIndice);
    }

    return noDados;
}

/*
Descrição: Escreve o nó de cabeçalho em seu arquivo de índice
@param arquivoIndice: arquivo de índice em que o nó de cabeçalho será escrito 
@param noCabecalho: no de cabecalho a ser escrito 
*/
void escreveNoCabecalhoNaAB(FILE *arquivoIndice, NoCabecalhoAB *noCabecalho) {

    fseek(arquivoIndice, 0, SEEK_SET);

    fwrite(&noCabecalho->status, 1, 1, arquivoIndice);
    fwrite(&noCabecalho->RRNraiz, sizeof(int), 1, arquivoIndice);
    fwrite(&noCabecalho->RRNproxNo, sizeof(int), 1, arquivoIndice);
    fwrite(noCabecalho->lixo, 1, 68, arquivoIndice);
}

/*
Descrição: Escreve um nó de dados em um arquivo de índice
@param arquivoIndice: arquivo de índice em que o nó de dados será escrito 
@param noCabecalho: no de dados a ser escrito 
*/
void escreveNoDadosNaAB(FILE *arquivoIndice, NoDadosAB *noDados) {

    fseek(arquivoIndice, (noDados->RRNdoNo + 1) * TAM_PAGINA, SEEK_SET); // (RRNdoNo + 1) por conta do no de cabeçalho

    // Escrevendo campos folha, nroChavesIndexada, RRNdoNo e primeiro filho:
    fwrite(&noDados->folha, 1, 1, arquivoIndice);
    fwrite(&noDados->nroChavesIndexadas, sizeof(int), 1, arquivoIndice);
    fwrite(&noDados->RRNdoNo, sizeof(int), 1, arquivoIndice);
    fwrite(&noDados->filhos[0], sizeof(int), 1, arquivoIndice);

    // Escrevendo chaves, bytes offsets e filhos da direita não nulos:
    for (int i = 0; i < noDados->nroChavesIndexadas; i++) {
        fwrite(&noDados->registros[i]->chave, sizeof(int), 1, arquivoIndice);
        fwrite(&noDados->registros[i]->byteOffset, sizeof(long long), 1, arquivoIndice);
        fwrite(&noDados->filhos[i+1], sizeof(int), 1, arquivoIndice);
    }

    int chaveNula = VALOR_NULO, filhoNulo = VALOR_NULO;
    long long byteOffsetNulo = VALOR_NULO;

    // Escrevendo chaves, bytes offsets e filhos da direita nulos (não preenchidos):
    for (int i = noDados->nroChavesIndexadas; i < ORDEM_ARVORE - 1; i++) {
        fwrite(&chaveNula, sizeof(int), 1, arquivoIndice);
        fwrite(&byteOffsetNulo, sizeof(long long), 1, arquivoIndice);
        fwrite(&filhoNulo, sizeof(int), 1, arquivoIndice);
    }
}

/*
Descrição: Insere um registro no arquivo de índice e rearranja as chaves de um nó cheio, 
movendo a metade maior para um nó com espaço. Por fim, sobrescreve o valor do parâmetro 
registroPromovido com os dados do registro que foi promovido durante a operação de split
@param arquivoIndice: arquivo de índice referente ao split realizado
@param noCheio: nó cheio que precisa ser "splitado"
@param noComEspaco: nó que tem espaço para receber metade das chaves do nó cheio
@param registroPromovido: registro promovido do nível inferior da função de inserção recursiva 
a ser inserido na operação de split
*/
void split(FILE *arquivoIndice, NoDadosAB *noCheio, NoDadosAB *noComEspaco, RegistroPromovido *registroPromovido) {

    // Inicializando um vetor de registros e um vetor de filhos para serem preenchidos
    // com as cópias dos registros e filhos do nó cheio. Ambos possuem 1 posição extra:
    RegistroDadosAB **copiaRegistros = alocaVetorRegistroDadosAB(ORDEM_ARVORE);
    int copiaFilhos[(ORDEM_ARVORE+1)];
    memset(copiaFilhos, VALOR_NULO, (ORDEM_ARVORE+1) * sizeof(int));

    // Preenchendo os vetores de cópia de registros e filhos:
    copiaFilhos[0] = noCheio->filhos[0];
    for (int i = 0; i < ORDEM_ARVORE - 1; i++) {
        copiaRegistros[i]->chave = noCheio->registros[i]->chave;
        copiaRegistros[i]->byteOffset = noCheio->registros[i]->byteOffset;
        copiaFilhos[i+1] = noCheio->filhos[i+1];
    }

    // Encontrando o índice de inserção da chave:
    int indiceInsercao;
    for (indiceInsercao = 0; indiceInsercao < ORDEM_ARVORE - 1; indiceInsercao++) {
        if (registroPromovido->chave < copiaRegistros[indiceInsercao]->chave)
            break;
    }

    // Shiftando as cópias dos registros e filhos para o registro ser inserido na posição correta:
    for (int i = (ORDEM_ARVORE-1); i > indiceInsercao; i--) {
        copiaRegistros[i]->chave = copiaRegistros[i-1]->chave;
        copiaRegistros[i]->byteOffset = copiaRegistros[i-1]->byteOffset;
        copiaFilhos[i+1] = copiaFilhos[i];
    }

    // Preenchendo os dados do registro e do filho da direita na posição adequada dos vetores de cópia:
    copiaRegistros[indiceInsercao]->chave = registroPromovido->chave;
    copiaRegistros[indiceInsercao]->byteOffset = registroPromovido->byteOffset;
    copiaFilhos[indiceInsercao+1] = registroPromovido->RRNfilhoDireita;

    /*  OBS: Nas linhas que precedem esse comentário registroPromovido guarda os dados do registro a ser 
        inserido no arquivo de índice. Uma vez inserido, ele passará a guardar os dados do registro que foi 
        promovido ao nível superior da árvore, para que ele possa ser acessado na função de inserção recursiva. */

    // Atribuindo os valores para o registro que deve ser promovido (o que está na posição central das cópias):
    registroPromovido->chave = copiaRegistros[(ORDEM_ARVORE/2)]->chave;
    registroPromovido->byteOffset = copiaRegistros[(ORDEM_ARVORE/2)]->byteOffset;
    registroPromovido->RRNfilhoDireita = noComEspaco->RRNdoNo;

    // Copiando a primeira metade das chaves/filhos ordenados dos vetores de cópia para a primeira metade do nó cheio:
    noCheio->filhos[0] = copiaFilhos[0];
    for (int i = 0; i < (ORDEM_ARVORE/2); i++) {
        noCheio->registros[i]->chave = copiaRegistros[i]->chave;
        noCheio->registros[i]->byteOffset = copiaRegistros[i]->byteOffset;
        noCheio->filhos[i+1] = copiaFilhos[i+1];
    }

    // Copiando a segunda metade das chaves/filhos ordenados dos vetores de cópia para a primeira metade do nó com espaço:
    noComEspaco->filhos[0] = copiaFilhos[(ORDEM_ARVORE/2+1)];
    for (int i = (ORDEM_ARVORE/2+1), j = 0; i < (ORDEM_ARVORE); i++, j++) {
        noComEspaco->registros[j]->chave = copiaRegistros[i]->chave;
        noComEspaco->registros[j]->byteOffset = copiaRegistros[i]->byteOffset;
        noComEspaco->filhos[j+1] = copiaFilhos[i+1];
    }

    // Atualizando o número de chaves indexadas pelos nós (metade do total):
    noCheio->nroChavesIndexadas = (ORDEM_ARVORE/2);
    noComEspaco->nroChavesIndexadas = (ORDEM_ARVORE/2);

    // Liberando memória extra alocada:
    liberaVetorRegistroDadosAB(copiaRegistros, ORDEM_ARVORE);
}

/*
Descrição: chama a si mesmo recursivamente a fim de inserir uma chave/byteoffset 
relativos a um registro em um arquivo de índice
@param arquivoIndice: arquivo de índice em que a chave/byteoffset serão inseridos
@param noCabecalho: nó de cabeçalho do arquivo de índice
@param RRNatual: RRN do nó atual da recursão (começa pela raíz)
@param chaveInserida: chave a ser inserida
@param byteOffset: byte offset da chave a ser inserida
@param registroPromovido: registro promovido do nível inferior da recursão (começa com valores nulos)
@return int 1 se precisar ser feita uma promoção ou 0 se não precisar ser feita nenhuma remoção
*/
bool insereRegistroRecursao(FILE *arquivoIndice, NoCabecalhoAB *noCabecalho, int RRNatual,
                            int chaveInserida, long long byteOffset, RegistroPromovido *registroPromovido)
{
    // Caso base da recursão: se o RRN atual for nulo, o nó do nível superior
    // é um nó folha, e, portanto, é nele em que a chave deve ser inserida.
    if (RRNatual == VALOR_NULO) {
        // Inicializando os campos do registro promovido para que ele possa ser inserido:
        registroPromovido->chave = chaveInserida;
        registroPromovido->byteOffset = byteOffset;
        registroPromovido->RRNfilhoDireita = VALOR_NULO;
        return true;
    }

    // Carregando o nó do RRN atual do arquivo de índice para a memória:
    NoDadosAB *noAtual = carregaNoDadosDaAB(arquivoIndice, RRNatual);

    // Obtendo a posição que a chave inserida deveria ocupar no nó atual:
    int indiceInsercao;
    for (indiceInsercao = 0; indiceInsercao < noAtual->nroChavesIndexadas; indiceInsercao++) {
        int chaveAtual = noAtual->registros[indiceInsercao]->chave;
        if (chaveInserida < chaveAtual)
            break;
    }

    // Chamando a recursão e verificando se há alguma promoção a ser feita:
    bool promocao = insereRegistroRecursao(arquivoIndice, noCabecalho, noAtual->filhos[indiceInsercao],
                                           chaveInserida, byteOffset, registroPromovido);

    // Se houver promoção a ser feita, não há mais nada a ser feito e a função deve retornar falso ao nível anterior:
    if (!promocao) {
        liberaNoDadosAB(noAtual);
        return false; // sem promoção
    }

    // Senão, o programa chegar nessa linha, e há uma promoção a ser feita: o registroPromovido deve ser inserido no nó atual

    // Se o nó atual tiver espaço, a chave é inserida normalmente:
    if (noAtual->nroChavesIndexadas < (ORDEM_ARVORE - 1)) {
        // Shiftando os registros/filhos do nó atual:
        for (int i = noAtual->nroChavesIndexadas; i > indiceInsercao; i--) {
            noAtual->registros[i]->chave = noAtual->registros[i-1]->chave;
            noAtual->registros[i]->byteOffset = noAtual->registros[i-1]->byteOffset;
            noAtual->filhos[i+1] = noAtual->filhos[i];
        }
        // Inserindo o registro no índice de inserção adequado:
        noAtual->registros[indiceInsercao]->chave = registroPromovido->chave;
        noAtual->registros[indiceInsercao]->byteOffset = registroPromovido->byteOffset;
        noAtual->filhos[indiceInsercao+1] = registroPromovido->RRNfilhoDireita;
        noAtual->nroChavesIndexadas += 1;
        noAtual->folha = noAtual->filhos[0] == VALOR_NULO ? '1' : '0';
        // Atualizando o nó atual no arquivo de índice:
        escreveNoDadosNaAB(arquivoIndice, noAtual);
        // Liberando memória alocada:
        liberaNoDadosAB(noAtual);
        return false; // sem nova promoção
    }

    // Senão, como o nó atual não tem espaço, deve ser realizada uma operação de split

    // Inicializando o nó extra splitado que receberá metade das chaves do nó atual:
    NoDadosAB *noNovo = alocaNoDadosAB();
    noNovo->RRNdoNo = noCabecalho->RRNproxNo++;
    noNovo->folha = noAtual->folha;

    // Realizando a operação de split:
    split(arquivoIndice, noAtual, noNovo, registroPromovido);

    // Atualizando o nó atual e inserindo o nó novo no arquivo de índice:
    escreveNoDadosNaAB(arquivoIndice, noAtual);
    escreveNoDadosNaAB(arquivoIndice, noNovo);

    // Liberando memória alocada:
    liberaNoDadosAB(noAtual);
    liberaNoDadosAB(noNovo);

    return true; // há uma promoção a ser feita
}

/*
Descrição: insere um par chave/byteOffset em um arquivo de índice
@param arquivoIndice: arquivo de índice em que a inserção será feita
@param noCabecalho: nó cabecalho do arquivo de índice
@param chaveInserida: chave a ser inserida
@param byteOffset: byteOffset relativo à chave inserida
*/
void insereRegistroDadosNaAB(FILE *arquivoIndice, NoCabecalhoAB *noCabecalho, int chaveInserida, long long byteOffset) {

    // Se a raiz tiver um valor nulo, o arquivo de índice deve ser inicializado 
    if (noCabecalho->RRNraiz == VALOR_NULO) {
        // Preenchendo os dados da primeira raiz:
        NoDadosAB *primeiraRaiz = alocaNoDadosAB();
        primeiraRaiz->nroChavesIndexadas += 1;
        primeiraRaiz->RRNdoNo = noCabecalho->RRNproxNo++;
        primeiraRaiz->registros[0]->chave = chaveInserida;
        primeiraRaiz->registros[0]->byteOffset = byteOffset;
        noCabecalho->RRNraiz = primeiraRaiz->RRNdoNo;
        // Atualizando o arquivo de índice:
        escreveNoCabecalhoNaAB(arquivoIndice, noCabecalho);
        escreveNoDadosNaAB(arquivoIndice, primeiraRaiz);
        // Liberando primeiraRaiz da memória:
        liberaNoDadosAB(primeiraRaiz);
        return;
    }

    // Inicializando o ponteiro de registroPromovido, que será usado na função de inserção recursiva:
    RegistroPromovido *registroPromovido = alocaRegistroPromovidoAB();

    // Inserindo a chave e o byteOffset e verificando se deve ser feita a promoção da raíz:
    bool promocao = insereRegistroRecursao(arquivoIndice, noCabecalho, noCabecalho->RRNraiz,
                                           chaveInserida, byteOffset, registroPromovido);

    // Se a raíz for promovida, seu valor deve ser atualizado:
    if (promocao) {
        // Atualizando os dados do novo nó raíz e do cabeçalho:
        NoDadosAB *novoNoRaiz = alocaNoDadosAB();
        novoNoRaiz->folha = '0';
        novoNoRaiz->nroChavesIndexadas = 1;
        novoNoRaiz->RRNdoNo = noCabecalho->RRNproxNo++;
        novoNoRaiz->registros[0]->chave = registroPromovido->chave;
        novoNoRaiz->registros[0]->byteOffset = registroPromovido->byteOffset;
        novoNoRaiz->filhos[0] = noCabecalho->RRNraiz;
        novoNoRaiz->filhos[1] = registroPromovido->RRNfilhoDireita;
        noCabecalho->RRNraiz = novoNoRaiz->RRNdoNo;
        // Atualizando o arquivo de índice e liberando nova raiz da memória:
        escreveNoCabecalhoNaAB(arquivoIndice, noCabecalho);
        escreveNoDadosNaAB(arquivoIndice, novoNoRaiz);
    }

    // Liberando memória alocada:
    free(registroPromovido);
}

/*
Descrição: função recursiva para busca de um registro em um arquivo de índice Árvore B
@param arquivoIndice: nome do arquivo de índice em que a busca será realizada
@param chaveBuscada: identificador único do registro buscado
@param buscaAtual: nó atual em que a busca será feita (começa pela raíz) 
@return O byte offset do registro buscado ou VALOR_NULO (-1) caso o registro não seja encontrado
*/
int buscaRegistroDadosNaABRecursiva(FILE *arquivoIndice, int chaveBuscada, NoDadosAB *buscaAtual) {

    // Caso base da recursão: não existem mais filhos para checar
    if (buscaAtual->RRNdoNo == VALOR_NULO) return VALOR_NULO;

    int indiceInsercao; // índice em que a chave buscada seria inserida
    for (indiceInsercao = 0; indiceInsercao < buscaAtual->nroChavesIndexadas; indiceInsercao++) {
        int chaveAtual = buscaAtual->registros[indiceInsercao]->chave;
        if (chaveAtual == chaveBuscada){
            return buscaAtual->registros[indiceInsercao]->byteOffset;
        }
        else if (chaveBuscada < chaveAtual)
            break;
    }

    // Chamando a recursão para o nó filho:
    NoDadosAB *novaBusca = carregaNoDadosDaAB(arquivoIndice, buscaAtual->filhos[indiceInsercao]);
    int resposta = buscaRegistroDadosNaABRecursiva(arquivoIndice, chaveBuscada, novaBusca);

    // Liberando memória alocada e retornando a resposta:
    liberaNoDadosAB(novaBusca);
    return resposta;
}

/* Descrição: busca a posição um registro de dados em um arquivo de índice do tipo Árvore B
@param arquivoIndice: nome do arquivo de índice em que a busca será realizada
@param cabecalho: nó de cabeçalho correspondente ao arquivo de índice
@param chaveBuscada: identificador único do registro buscado
@return O byte offset do registro buscado ou VALOR_NULO (-1) caso o registro não seja encontrado
*/
long long buscaRegistroDadosNaAB(FILE *arquivoIndice, NoCabecalhoAB *cabecalho, int chaveBuscada) {
    NoDadosAB *buscaAtual = carregaNoDadosDaAB(arquivoIndice, cabecalho->RRNraiz);
    int byteOffSet = buscaRegistroDadosNaABRecursiva(arquivoIndice, chaveBuscada, buscaAtual);
    liberaNoDadosAB(buscaAtual);
    return byteOffSet;
}