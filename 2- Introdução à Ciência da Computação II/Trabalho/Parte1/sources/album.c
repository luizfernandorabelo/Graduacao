#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "album.h"

#define NOT_FOUND -1


struct album_{
    char *name;
    char *id;
    int numberOfTracks;
    TRACK **tracks;
};


ALBUM *albumAlocate(void){

    ALBUM *album = malloc(sizeof(ALBUM));

    if(album != NULL){
        album->name = NULL;
        album->id = NULL;
        album->numberOfTracks = 0;
        album->tracks = NULL;
    }

    return(album);
}


void albumFree(ALBUM **album){

    if(*album == NULL)
        return;  

    if((*album)->name != NULL) 
        free((*album)->name); 

    if((*album)->id != NULL) 
        free((*album)->id); 

    if((*album)->tracks != NULL){ 
        for(int i = 0; i < (*album)->numberOfTracks; i++)
            trackFree(&(*album)->tracks[i]);
        free((*album)->tracks);
    }

    free(*album);
    *album = NULL;
}


void albumSetName(ALBUM *album, char *albumName){

    if(album != NULL)
        album->name = albumName;
}


void albumSetId(ALBUM *album, char *id){

    if(album != NULL)
        album->id = id;
}


int getTrackInsertionIndex(ALBUM *album, char *trackId){

    int index = 0;

    while(index < album->numberOfTracks && strcmp(trackGetId(album->tracks[index]), trackId) < 0)
        index += 1;

    return(index);    
}


void albumInsertTrack(ALBUM *album, TRACK *track){

    if(album != NULL){
        album->tracks = realloc(album->tracks, (album->numberOfTracks+1) * sizeof(TRACK *));
        
        int insertionIndex = album->numberOfTracks;

        #ifdef ALBUM_SORTED_BY_TRACK_ID 
            insertionIndex = getTrackInsertionIndex(album, trackGetId(track));
            for(int i = album->numberOfTracks; i > insertionIndex; i--)
                album->tracks[i] = album->tracks[i-1];
        #endif

        album->tracks[insertionIndex] = track;
        album->numberOfTracks += 1;
    }
}


void checkAlbumContent(ALBUM *album){
    
    if(album == NULL){
        printf("Album access failure! The album points to no content\n");
        exit(ALBUM_ACCESS_FAILURE);
    }
}


char *albumGetName(ALBUM *album){

    checkAlbumContent(album);

    return(album->name);
}


char *albumGetId(ALBUM *album){

    checkAlbumContent(album);

    return(album->id);
}


int albumGetNumberOfTracks(ALBUM *album){

    checkAlbumContent(album);

    return(album->numberOfTracks);
}


int albumGetTracksPopularitySum(ALBUM *album){

    checkAlbumContent(album);

    int popularitySum = 0;

    for(int i = 0; i < album->numberOfTracks; i++)
        popularitySum += trackGetPopularity(album->tracks[i]);

    return(popularitySum);
}


int trackBinarySearch(ALBUM *album, char *trackId){

    int start = 0, end = album->numberOfTracks-1, half;

    while(end >= start){
        half = (end + start) / 2;
        if(strcmp(trackGetId(album->tracks[half]), trackId) == 0)
            return(half);
        else if(strcmp(trackGetId(album->tracks[half]), trackId) < 0)
            start = half + 1;
        else
            end = half - 1;
    }

    return(NOT_FOUND);
}


TRACK *albumGetTrack(ALBUM *album, char *trackId){

    checkAlbumContent(album);

    #ifdef ALBUM_SORTED_BY_TRACK_ID 
        int index = trackBinarySearch(album, trackId);
        return((index != NOT_FOUND) ? album->tracks[index] : NULL);
    #else
        for(int i = 0; i < album->numberOfTracks; i++){
            char *currentId = trackGetId(album->tracks[i]);
            if(strcmp(currentId, trackId) == 0)
                return(album->tracks[i]);
        }
        return(NULL);
    #endif
}