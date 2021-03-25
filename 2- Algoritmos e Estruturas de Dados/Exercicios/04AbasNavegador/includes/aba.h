#ifndef ABA_H
    #define ABA_H

    #ifndef BOOLEAN_TYPE
        #define BOOLEAN_TYPE

        #define bool char
        #define True 1
        #define False 0
    #endif    

    #define TAM_TITULO 40
    #define TAM_URL 512

    typedef struct aba_ ABA;

    ABA *aba_criar();
    bool aba_set_titulo(ABA *aba, char *titulo);
    bool aba_set_url(ABA *aba, char *url);
    char *aba_get_titulo(ABA *aba);
    char *aba_get_url(ABA *aba);
    void aba_imprimir(ABA *aba);
    bool aba_apagar(ABA **aba);
     
#endif