#include <stdio.h>
#include <stdlib.h>

#include "track.h"


struct track_{
    char *name;
    char *id;
    char *albumId;
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
};


TRACK *trackALocate(void){

    TRACK *track = malloc(sizeof(TRACK));
    
    if(track != NULL){
        track->name = NULL;
        track->id = NULL;
        track->albumId = NULL;
        track->artistId = NULL;
        track->releaseDate = NULL;
        track->lenght = 0;
        track->popularity = 0;
        track->acousticness = 0;
        track->danceability = 0;
        track->energy = 0;
        track->instrumentalness = 0;
        track->liveness = 0;
        track->loudness = 0;
        track->speechness = 0;
        track->time = 0;
        track->timeSignature = 0;
    }

    return(track);
}


void trackFree(TRACK **track){

    if(*track == NULL)
        return;

    if((*track)->name != NULL){ 
        free((*track)->name);
        (*track)->name = NULL;
    }

    if((*track)->id != NULL){ 
        free((*track)->id);
        (*track)->id = NULL;
    }

    if((*track)->albumId != NULL){
        free((*track)->albumId);
        (*track)->albumId = NULL;
    }

    if((*track)->artistId != NULL){
        free((*track)->artistId);
        (*track)->artistId = NULL;
    }

    if((*track)->releaseDate != NULL){
        free((*track)->releaseDate);
        (*track)->releaseDate = NULL;
    }

    free(*track); *track = NULL;
}


void trackSetName(TRACK *track, char *trackName){

    if(track != NULL)
        track->name = trackName;    
}


void trackSetId(TRACK *track, char *id){

    if(track != NULL)
        track->id = id;    
}


void trackSetAlbumId(TRACK *track, char *albumId){

    if(track != NULL)
        track->albumId = albumId;    
}


void trackSetArtistId(TRACK *track, char *artistId){

    if(track != NULL)
        track->artistId = artistId;    
}


void trackSetReleaseDate(TRACK *track, char *releaseDate){

    if(track != NULL)
        track->releaseDate = releaseDate;    
}


void trackSetLenght(TRACK *track, int lenght){

    if(track != NULL)
        track->lenght = lenght;    
}


void trackSetPopularity(TRACK *track, int popularity){

    if(track != NULL)
        track->popularity = popularity;    
}


void trackSetAcousticness(TRACK *track, double acousticness){

    if(track != NULL)
        track->acousticness = acousticness;    
}


void trackSetDanceability(TRACK *track, double danceability){

    if(track != NULL)
        track->danceability = danceability;    
}


void trackSetEnergy(TRACK *track, double energy){

    if(track != NULL)
        track->energy = energy;    
}


void trackSetInstrumentalness(TRACK *track, double instrumentalness){

    if(track != NULL)
        track->instrumentalness = instrumentalness;    
}


void trackSetLiveness(TRACK *track, double liveness){

    if(track != NULL)
        track->liveness = liveness;    
}


void trackSetLoudness(TRACK *track, double loudness){

    if(track != NULL)
        track->loudness = loudness;    
}


void trackSetSpeechness(TRACK *track, double speechness){

    if(track != NULL)
        track->speechness = speechness;    
}


void trackSetTime(TRACK *track, double time){

    if(track != NULL)
        track->time = time;    
}

void trackSetTimeSignature(TRACK *track, int timeSignature){

    if(track != NULL)
        track->timeSignature = timeSignature;    
}


void checkTrackContent(TRACK *track){
    
    if(track == NULL){
        printf("Track access failure! The track points to no content\n");
        exit(TRACK_ACCESS_FAILURE);
    }
}


char *trackGetName(TRACK *track){

    checkTrackContent(track);

    return(track->name);
}


char *trackGetId(TRACK *track){

    checkTrackContent(track);

    return(track->id);
}


char *trackGetAlbumId(TRACK *track){

    checkTrackContent(track);

    return(track->albumId);
}


char *trackGetArtistId(TRACK *track){

    checkTrackContent(track);

    return(track->artistId);
}


char *trackGetReleaseDate(TRACK *track){

    checkTrackContent(track);

    return(track->releaseDate);
}


int trackGetLenght(TRACK *track){

    checkTrackContent(track);

    return(track->lenght);
}


int trackGetPopularity(TRACK *track){

    checkTrackContent(track);

    return(track->popularity);
}


double trackGetAcousticness(TRACK *track){

    checkTrackContent(track);

    return(track->acousticness);
}


double trackGetDanceability(TRACK *track){

    checkTrackContent(track);

    return(track->danceability);
}


double trackGetEnergy(TRACK *track){

    checkTrackContent(track);

    return(track->energy);
}


double trackGetInstrumentalness(TRACK *track){

    checkTrackContent(track);

    return(track->instrumentalness);
}


double trackGetLiveness(TRACK *track){

    checkTrackContent(track);

    return(track->liveness);
}


double trackGetLoudness(TRACK *track){

    checkTrackContent(track);

    return(track->loudness);
}


double trackGetSpeechness(TRACK *track){

    checkTrackContent(track);

    return(track->speechness);
}


double trackGetTime(TRACK *track){

    checkTrackContent(track);

    return(track->time);
}


int trackGetTimeSignature(TRACK *track){

    checkTrackContent(track);

    return(track->timeSignature);
}