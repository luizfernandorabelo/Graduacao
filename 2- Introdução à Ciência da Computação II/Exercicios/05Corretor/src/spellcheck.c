#include <stdio.h>
#include <stdlib.h>

#include "jsonTweet.h"
#include "dictionary.h"


int main(int argc, char *argv[]){

    //Leitura e Armazanamento dos Nomes dos Arquivos Livro e Json:
    char bookFileName[50], tweetsFileName[50];
    scanf("%s" "%s", bookFileName, tweetsFileName);

    //Carregamento do Dicionário e das Palavras dos Tweets para a Memória:
    dictionary_t *dictionary = loadDictionaryFromTxtFile(bookFileName);
    tweet_words_t **tweetWords = getTweetWordsFromJsonFile(tweetsFileName);

    //Impressão das Palavras Incorretas:
    if(tweetWords == NULL){
        printf("No tweets to check\n");
    }
    else{
        for(int i = 0; tweetWords[i] != NULL; i++){
            tweet_words_t *currentTweet = tweetWords[i];
            for(int j = 0; j < currentTweet->size; j++){
                char *currentWord = currentTweet->words[j];
                if(!isWordInDictionary(currentWord, dictionary))
                    printf("%s ", currentWord);
            }
            printf("\n");
        }
    }

    //Liberação de Memória Alocada:
    deleteTweetWords(tweetWords);
    unloadDictionary(dictionary);

    return(0);
}