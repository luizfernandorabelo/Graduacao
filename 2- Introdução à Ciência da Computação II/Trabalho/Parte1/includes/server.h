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

    #define SERVER_SORTED_BY_ARTIST_ID 

    #define SERVER_ACCESS_FAILURE 0

    typedef struct server_ SERVER;

    SERVER *serverALocate(void);
    void serverFree(SERVER **server);
    void serverInsertArtist(SERVER *server, ARTIST *artist);
    void serverLoadFromCsvFile(SERVER *server, char *fileName);
    void serverPrintArtistsByPopularity(SERVER *server);
    int serverGetNumberOfArtists(SERVER *server);
    int serverGetNumberOfAlbums(SERVER *server);
    int serverGetNumberOfTracks(SERVER *server);
    ARTIST *serverGetArtist(SERVER *server, char *artistId);

#endif