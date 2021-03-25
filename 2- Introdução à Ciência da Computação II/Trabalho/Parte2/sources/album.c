#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "album.h"


struct album_{
    char *name;
    char *id;
    int numberOfTracks;
};


ALBUM *albumAlocate(void){

    ALBUM *album = malloc(sizeof(ALBUM));

    if(album != NULL){
        album->name = NULL;
        album->id = NULL;
        album->numberOfTracks = 0;
    }

    return(album);
}


void albumFree(ALBUM **album){
    
    if(*album == NULL)
        return;

    if((*album)->name != NULL){
        free((*album)->name);
        (*album)->name = NULL;
    }

    free(*album); *album = NULL;
}


void albumSetName(ALBUM *album, char *albumName){

    if(album != NULL)
        album->name = albumName;
}


void albumSetId(ALBUM *album, char *id){

    if(album != NULL)
        album->id = id;
}


void albumSetNumberOfTracks(ALBUM *album, int numberOfTracks){

    if(album != NULL)
        album->numberOfTracks = numberOfTracks;
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