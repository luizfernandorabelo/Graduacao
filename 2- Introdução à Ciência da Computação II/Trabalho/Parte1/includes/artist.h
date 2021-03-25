#ifndef ARTIST_H
    #define ARTIST_H

    #include "track.h"
    #include "album.h"

    #define ARTIST_ALBUMS_SORTED_BY_ID 

    #define ARTIST_ACCESS_FAILURE 0
    
    typedef struct artist_ ARTIST;

    ARTIST *artistAlocate(void);
    void artistFree(ARTIST **artist);
    void artistSetName(ARTIST *artist, char *name);
    void artistSetId(ARTIST *artist, char *id);
    void artistInsertAlbum(ARTIST *artist, ALBUM *album);
    char *artistGetName(ARTIST *artist);
    char *artistGetId(ARTIST *artist);
    double artistGetPopularity(ARTIST *artist);
    int artistGetNumberOfAlbums(ARTIST *artist);
    int artistGetNumberOfTracks(ARTIST *artist);
    ALBUM *artistGetAlbum(ARTIST *artist, char *albumId);

#endif