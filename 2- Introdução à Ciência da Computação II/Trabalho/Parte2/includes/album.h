#ifndef ALBUM_H
    #define ALBUM_H

    #include "track.h"
    
    #define ALBUM_ACCESS_FAILURE 0 

    typedef struct album_ ALBUM;

    ALBUM *albumAlocate(void);
    void albumFree(ALBUM **album);
    void albumSetName(ALBUM *album, char *albumName);
    void albumSetId(ALBUM *album, char *id);
    void albumSetNumberOfTracks(ALBUM *album, int numberOfTracks);
    char *albumGetName(ALBUM *album);
    char *albumGetId(ALBUM *album);
    int albumGetNumberOfTracks(ALBUM *album);

#endif