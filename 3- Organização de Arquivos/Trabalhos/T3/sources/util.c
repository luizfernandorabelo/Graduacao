// - Felipe Cadavez Oliveira (11208558)
// - Luiz Fernando Rabelo (11796893)

#include "util.h"

/*
Descrição: função de comparação da qsort para ordenação de veículos
*/
int comparVeiculos(const void *a, const void *b) {
    return (*(RegistroVeiculo **) a)->codLinha - (*(RegistroVeiculo **) b)->codLinha;
}

/*
Descrição: função de comparação da qsort para ordenação de veículos
*/
int comparLinhas(const void *a, const void *b) {
    return (*(RegistroLinha **) a)->codLinha - (*(RegistroLinha **) b)->codLinha;
}

/*
Descrição: obtém o mês do ano correspondente a partir de seu número
@param num número do mês
@return um ponteiro com uma cadeia de caracteres representando o mês correspondente
*/
char* verMes(int num){
    char *mes = malloc(15*sizeof(char));
    switch (num)
    {
        case 1:
            strcpy(mes, "janeiro");
            break;
        case 2:
            strcpy(mes, "fevereiro");
            break;
        case 3:
            strcpy(mes, "março");
            break;
        case 4:
            strcpy(mes, "abril");
            break;
        case 5:
            strcpy(mes, "maio");
            break;
        case 6:
            strcpy(mes, "junho");
            break;
        case 7:
            strcpy(mes, "julho");
            break;
        case 8:
            strcpy(mes, "agosto");
            break;
        case 9:
            strcpy(mes, "setembro");
            break;
        case 10:
            strcpy(mes, "outubro");
            break;
        case 11:
            strcpy(mes, "novembro");
            break;
        case 12:
            strcpy(mes, "dezembro");
            break;
        default:
            mes = NULL;
            break;
    }
    return mes;
}

/*
Descrição: Imprime a mensagem "Falha no processamento do arquivo."
@param stream fluxo no qual a mensagem será impressa
*/
void imprimeMensagemErro(FILE *stream) {
	fprintf(stream, "Falha no processamento do arquivo.\n");
}

/*
Descrição: Verifica se o fluxo passado por parâmetro chegou ao seu fim
@param arquivoBIN: fluxo do arquivo binário a ser verificado
@return int 1 se verdadeiro | 0 se falso
*/
int fimDoArquivoBIN(FILE *arquivoBIN) {

    char byteAtual;
    fread(&byteAtual, 1, 1, arquivoBIN);

    if (feof(arquivoBIN)) 
        return 1; 
    
    fseek(arquivoBIN, -1, SEEK_CUR); // voltamos um byte (pois "comemos" um char válido)
    return 0;
}



//// Função desenvolvida pelos monitores:

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}
