#ifndef CSV_READER_H
    #define CSV_READER_H

    #ifndef booleanType
        #define booleanType

        #define bool int
        #define True 1
        #define False 0
    #endif

    #define FILE_OPEN_FAILURE 0
    #define FIELD_DELIMITER ';'

    typedef struct{
        char **fieldNames;
        int numberOfFields;
    }HEADER;

    typedef struct{
        char *trackName;
        char *trackId;
        char *albumName;
        char *albumId;
        char *artistName;
        char *artistId;
        char *releaseDate;
        int lenght;
        int popularity;
        double acousticness;
        double danceability;
        double energy;
        double instrumentalness;
        double liveness;
        double loudness;
        double speechness;
        double time;
        int timeSignature;
    }REGISTER;
    
    typedef struct{
        HEADER *header;
        REGISTER **registers;
        int numberOfRegisters;
    }CSV;

    CSV *csvReadData(char *fileName);

#endif 