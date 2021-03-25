#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "artist.h"

#define NOT_FOUND -1


struct artist_{
    char *name;
    char *id;
    ALBUM **albums;
    int numberOfAlbums;
};


ARTIST *artistAlocate(void){

    ARTIST *artist = malloc(sizeof(ARTIST));

    if(artist != NULL){
        artist->name = NULL;
        artist->id = NULL;
        artist->albums = NULL;
        artist->numberOfAlbums = 0;
    }

    return(artist);
}


void artistFree(ARTIST **artist){

    if(*artist == NULL)
        return;

    if((*artist)->name != NULL)
        free((*artist)->name);

    if((*artist)->id != NULL)
        free((*artist)->id);

    if((*artist)->albums != NULL){
        for(int i = 0; i < (*artist)->numberOfAlbums; i++)
            albumFree(&(*artist)->albums[i]);            
        free((*artist)->albums);
    } 

    free(*artist);
    *artist = NULL;
}


void artistSetName(ARTIST *artist, char *name){

    if(artist != NULL)
        artist->name = name;
}


void artistSetId(ARTIST *artist, char *id){

    if(artist != NULL)
        artist->id = id;
}


int getAlbumInsertionIndex(ARTIST *artist, char *albumId){

    int index = 0;

    while(index < artist->numberOfAlbums && strcmp(albumGetId(artist->albums[index]), albumId) < 0)
        index += 1;

    return(index);
}


void artistInsertAlbum(ARTIST *artist, ALBUM *album){

    if(artist != NULL){
        artist->albums = realloc(artist->albums, (artist->numberOfAlbums+1) * sizeof(ALBUM *));

        int insertionIndex = artist->numberOfAlbums;

        #ifdef ARTIST_ALBUMS_SORTED_BY_ID
            insertionIndex = getAlbumInsertionIndex(artist, albumGetId(album));
            for(int i = artist->numberOfAlbums; i > insertionIndex; i--)
                artist->albums[i] = artist->albums[i-1];
        #endif 

        artist->albums[insertionIndex] = album;
        artist->numberOfAlbums += 1;
    }
}


void checkArtitsContent(ARTIST *artist){

    if(artist == NULL){
        printf("Artist access failure! The artist points to no content\n");
        exit(ARTIST_ACCESS_FAILURE);
    }
}


char *artistGetName(ARTIST *artist){

    checkArtitsContent(artist);

    return(artist->name);
}


char *artistGetId(ARTIST *artist){

    checkArtitsContent(artist);

    return(artist->id);
}


double artistGetPopularity(ARTIST *artist){

    checkArtitsContent(artist);

    double popularitySum = 0;
    
    for(int i = 0; i < artist->numberOfAlbums; i++)
        popularitySum += albumGetTracksPopularitySum(artist->albums[i]);

    return((double) popularitySum / artistGetNumberOfTracks(artist));
}


int artistGetNumberOfAlbums(ARTIST *artist){

    checkArtitsContent(artist);

    return(artist->numberOfAlbums);
}


int artistGetNumberOfTracks(ARTIST *artist){

    checkArtitsContent(artist);

    int numberOfTracks = 0;

    for(int i = 0; i < artist->numberOfAlbums; i++)
        numberOfTracks += albumGetNumberOfTracks(artist->albums[i]);

    return(numberOfTracks);
}


int albumBinarySearch(ARTIST *artist, char *albumId){

    int start = 0, end = artist->numberOfAlbums-1, half;

    while(end >= start){
        half = (end + start) / 2;
        if(strcmp(albumGetId(artist->albums[half]), albumId) == 0)
            return(half);
        else if(strcmp(albumGetId(artist->albums[half]), albumId) < 0)
            start = half + 1;
        else 
            end = half - 1;
    }

    return(NOT_FOUND);
}


ALBUM *artistGetAlbum(ARTIST *artist, char *albumId){

    checkArtitsContent(artist);

    #ifdef ARTIST_ALBUMS_SORTED_BY_ID     
        int index = albumBinarySearch(artist, albumId);
        return((index != NOT_FOUND) ? artist->albums[index] : NULL);
    #else
        for(int i = 0; i < artist->numberOfAlbums; i++){
            char *currentId = albumGetId(artist->albums[i]);
            if(strcmp(currentId, albumId) == 0)
                return(artist->albums[i]);
        }
        return(NULL);
    #endif
}