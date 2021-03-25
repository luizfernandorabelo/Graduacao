#ifndef SERVER_H
    #define SERVER_H

    #ifndef booleanType
        #define booleanType

        #define bool int
        #define True 1
        #define False 0
    #endif

    #include "track.h"
    #include "album.h"
    #include "artist.h"
    #include "csvReader.h"

    #define SERVER_ACCESS_FAILURE 0

    typedef struct server_ SERVER;

    SERVER *serverALocate(void);
    void serverFree(SERVER **server);
    void serverLoadFromCsvFile(SERVER *server, char *fileName);
    void serverPrintArtistsByPopularity(SERVER *server);
    void serverPrintMostSimilarTracks(SERVER *server, char *trackId, int numberOfSimilar);
    int serverGetNumberOfArtists(SERVER *server);
    int serverGetNumberOfAlbums(SERVER *server);
    int serverGetNumberOfTracks(SERVER *server);

#endif