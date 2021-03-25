#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "artist.h"


struct artist_{
    char *name;
    char *id;
    int numberOfAlbums;
    int numberOfTracks;
    double popularity;
};


ARTIST *artistAlocate(void){

    ARTIST *artist = malloc(sizeof(ARTIST));

    if(artist != NULL){
        artist->name = NULL;
        artist->id = NULL;
        artist->numberOfAlbums = 0;
        artist->numberOfTracks = 0;
        artist->popularity = 0.0;
    }

    return(artist);
}


void artistFree(ARTIST **artist){

    if(*artist == NULL)
        return;
    
    if((*artist)->name != NULL){
        free((*artist)->name);
        (*artist)->name = NULL;
    }

    free(*artist); *artist = NULL;
}


void artistSetName(ARTIST *artist, char *name){

    if(artist != NULL)
        artist->name = name;
}


void artistSetId(ARTIST *artist, char *id){

    if(artist != NULL)
        artist->id = id;
}


void artistSetNumberOfAlbums(ARTIST *artist, int numberOfAlbums){

    if(artist != NULL)
        artist->numberOfAlbums = numberOfAlbums;
}


void artistSetNumberOfTracks(ARTIST *artist, int numberOfTracks){

    if(artist != NULL)
        artist->numberOfTracks = numberOfTracks;
}


void artistSetPopularity(ARTIST *artist, double popularity){

    if(artist != NULL)
        artist->popularity = popularity;
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

    return(artist->popularity);
}


int artistGetNumberOfAlbums(ARTIST *artist){

    checkArtitsContent(artist);

    return(artist->numberOfAlbums);
}


int artistGetNumberOfTracks(ARTIST *artist){

    checkArtitsContent(artist);

    return(artist->numberOfTracks);
}