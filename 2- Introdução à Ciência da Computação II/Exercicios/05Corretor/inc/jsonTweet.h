#ifndef JSON_TWEET_H
    #define JSON_TWEET_H

    #ifndef booleanType
        #define booleanType

        #define bool char
        #define True 1
        #define False 0
    #endif

    #define TWEET_FIELD_NAME "text"

    typedef struct{
        char **words;
        int size;
    }tweet_words_t;

    tweet_words_t **getTweetWordsFromJsonFile(char *fileName);
    void deleteTweetWords(tweet_words_t **tweetWords);

#endif