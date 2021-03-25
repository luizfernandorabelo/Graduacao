#ifndef ALBUM_H
    #define ALBUM_H

    #include "track.h"
    
    #define ALBUM_SORTED_BY_TRACK_ID 
    
    #define ALBUM_ACCESS_FAILURE 0 

    typedef struct album_ ALBUM;

    ALBUM *albumAlocate(void);
    void albumFree(ALBUM **album);
    void albumSetName(ALBUM *album, char *albumName);
    void albumSetId(ALBUM *album, char *id);
    void albumInsertTrack(ALBUM *album, TRACK *track);
    void albumSortTrackById(ALBUM *album);
    char *albumGetName(ALBUM *album);
    char *albumGetId(ALBUM *album);
    int albumGetNumberOfTracks(ALBUM *album);
    int albumGetTracksPopularitySum(ALBUM *album);
    TRACK *albumGetTrack(ALBUM *album, char *trackId);

#endif