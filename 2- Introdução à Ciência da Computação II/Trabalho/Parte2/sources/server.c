#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "server.h"

#define NOT_FOUND -1 
#define DISCREETZATION_FACTOR 1000000


struct server_{
    ARTIST **artists;
    ALBUM **albums;
    TRACK **tracks;
    int numberOfArtists;
    int numberOfAlbums;
    int numberOfTracks;
    double **dissimilarityMatrix;
};

typedef struct{
    double distance;
    int trackIndex;
}DISSIMILARITY;

typedef struct{
    DISSIMILARITY **line;
}DISSIMILARITY_LINE;


SERVER *serverALocate(void){

    SERVER *server = malloc(sizeof(SERVER));

    if(server != NULL){
        server->artists = NULL;
        server->albums = NULL;
        server->tracks = NULL;
        server->numberOfArtists = 0;
        server->numberOfAlbums = 0;
        server->numberOfTracks = 0;
        server->dissimilarityMatrix = NULL;
    }

    return(server);
}


void serverFreeArtists(SERVER **server){

    if((*server)->artists != NULL){
        for(int i = 0; i < (*server)->numberOfArtists; i++)
            artistFree(&(*server)->artists[i]);
        free((*server)->artists);
        (*server)->artists = NULL;
    }
}


void serverFreeAlbums(SERVER **server){

    if((*server)->albums != NULL){
        for(int i = 0; i < (*server)->numberOfAlbums; i++)
            albumFree(&(*server)->albums[i]);
        free((*server)->albums);
        (*server)->albums = NULL;
    }
}


void serverFreeTracks(SERVER **server){

    if((*server)->tracks != NULL){
        for(int i = 0; i < (*server)->numberOfTracks; i++)
            trackFree(&(*server)->tracks[i]);
        free((*server)->tracks);
        (*server)->tracks = NULL;
    }
}


void serverFreeDissimilarityMatrix(SERVER **server){

    if((*server)->dissimilarityMatrix != NULL){
        for(int i = 0; i < (*server)->numberOfTracks; i++){
            if((*server)->dissimilarityMatrix[i] != NULL){
                free((*server)->dissimilarityMatrix[i]);
                (*server)->dissimilarityMatrix[i] = NULL;
            }
        }
        free((*server)->dissimilarityMatrix);
        (*server)->dissimilarityMatrix = NULL;
    }
}


void serverFree(SERVER **server){

    if(*server != NULL){
        serverFreeArtists(server);
        serverFreeAlbums(server);
        serverFreeTracks(server);
        serverFreeDissimilarityMatrix(server);
        free(*server); *server = NULL;
    }
}


void checkServerContent(SERVER *server){

    if(server == NULL){
        printf("Server access failure! The server points to no content\n");
        exit(SERVER_ACCESS_FAILURE);
    }
}


int artistBinarySearch(SERVER *server, char *artistId){

    int start = 0, end = server->numberOfArtists-1, half;

    while(end >= start){
        half = (end + start) / 2;
        if(strcmp(artistGetId(server->artists[half]), artistId) == 0)
            return(half);
        else if(strcmp(artistGetId(server->artists[half]), artistId) < 0)
            start = half + 1;
        else
            end = half - 1;
    }
    
    return(NOT_FOUND);
}


ARTIST *serverGetArtist(SERVER *server, char *artistId){

    checkServerContent(server);

    int index = artistBinarySearch(server, artistId);

    return((index != NOT_FOUND) ? server->artists[index] : NULL);
}


int albumBinarySearch(SERVER *server, char *albumId){

    int start = 0, end = server->numberOfAlbums-1, half;

    while(end >= start){
        half = (end + start) / 2;
        if(strcmp(albumGetId(server->albums[half]), albumId) == 0)
            return(half);
        else if(strcmp(albumGetId(server->albums[half]), albumId) < 0)
            start = half + 1;
        else
            end = half - 1;
    }
    
    return(NOT_FOUND);
}


ALBUM *serverGetAlbum(SERVER *server, char *albumId){

    checkServerContent(server);

    int index = albumBinarySearch(server, albumId);

    return((index != NOT_FOUND) ? server->albums[index] : NULL);
}


int trackBinarySearch(SERVER *server, char *trackId){

    int start = 0, end = server->numberOfTracks-1, half;

    while(end >= start){
        half = (end + start) / 2;
        if(strcmp(trackGetId(server->tracks[half]), trackId) == 0)
            return(half);
        else if(strcmp(trackGetId(server->tracks[half]), trackId) < 0)
            start = half + 1;
        else
            end = half - 1;
    }
    
    return(NOT_FOUND);
}


TRACK *serverGetTrack(SERVER *server, char *trackId){

    checkServerContent(server);

    int index = trackBinarySearch(server, trackId);

    return((index != NOT_FOUND) ? server->tracks[index] : NULL);
}



int getArtistInsertionIndex(SERVER *server, char *artistId){

    int index = 0;

    while(index < server->numberOfArtists && strcmp(artistGetId(server->artists[index]), artistId) < 0)
        index += 1;
    
    return(index);
}


void serverInsertArtist(SERVER *server, ARTIST *artist){

    if(server != NULL){
        server->artists = realloc(server->artists, (server->numberOfArtists + 1) * sizeof(ARTIST *));

        int insertionIndex = getArtistInsertionIndex(server, artistGetId(artist));

        for(int i = server->numberOfArtists; i > insertionIndex; i--)
            server->artists[i] = server->artists[i-1];

        server->artists[insertionIndex] = artist;
        server->numberOfArtists += 1;
    }
}


int getAlbumInsertionIndex(SERVER *server, char *albumId){

    int index = 0;

    while(index < server->numberOfAlbums && strcmp(albumGetId(server->albums[index]), albumId) < 0)
        index += 1;

    return(index);
}


void serverInsertAlbum(SERVER *server, ALBUM *album){

    if(server != NULL){
        server->albums = realloc(server->albums, (server->numberOfAlbums + 1) * sizeof(ALBUM *));

        int insertionIndex = getAlbumInsertionIndex(server, albumGetId(album));

        for(int i = server->numberOfAlbums; i > insertionIndex; i--)
            server->albums[i] = server->albums[i-1];
        
        server->albums[insertionIndex] = album;
        server->numberOfAlbums += 1;
    }
}


int getTrackInsertionIndex(SERVER *server, char *trackId){

    int index = 0;

    while(index < server->numberOfTracks && strcmp(trackGetId(server->tracks[index]), trackId) < 0)
        index += 1;

    return(index);
}


void serverInsertTrack(SERVER *server, TRACK *track){

    if(server != NULL){
        server->tracks = realloc(server->tracks, (server->numberOfTracks + 1) * sizeof(TRACK *));

        int insertionIndex = getTrackInsertionIndex(server, trackGetId(track));

        for(int i = server->numberOfTracks; i > insertionIndex; i--)
            server->tracks[i] = server->tracks[i-1];
        
        server->tracks[insertionIndex] = track;
        server->numberOfTracks += 1;
    }
}


double getArtistPopularity(SERVER *server, ARTIST *artist){

    int popularitySum = 0, totalArtistTracks = artistGetNumberOfTracks(artist);

    for(int i = 0; i < server->numberOfTracks; i++){
        if(strcmp(trackGetArtistId(server->tracks[i]), artistGetId(artist)) == 0)
            popularitySum += trackGetPopularity(server->tracks[i]);
    }

    return((totalArtistTracks > 0) ? (double) popularitySum / totalArtistTracks : 0.0);
}


double getDistance(TRACK *track1, TRACK *track2){

    double diffSquaredSum = 0.0;

    diffSquaredSum += pow((trackGetAcousticness(track1) - trackGetAcousticness(track2)), 2.0);
    diffSquaredSum += pow((trackGetDanceability(track1) - trackGetDanceability(track2)), 2.0);
    diffSquaredSum += pow((trackGetEnergy(track1) - trackGetEnergy(track2)), 2.0);
    diffSquaredSum += pow((trackGetInstrumentalness(track1) - trackGetInstrumentalness(track2)), 2.0);
    diffSquaredSum += pow((trackGetLiveness(track1) - trackGetLiveness(track2)), 2.0);
    diffSquaredSum += pow((trackGetLoudness(track1) - trackGetLoudness(track2)), 2.0);
    diffSquaredSum += pow((trackGetSpeechness(track1) - trackGetSpeechness(track2)), 2.0);
    diffSquaredSum += pow((trackGetTime(track1) - trackGetTime(track2)), 2.0);
    diffSquaredSum += pow(((double) trackGetTimeSignature(track1) - (double) trackGetTimeSignature(track2)), 2.0);

    return(sqrt(diffSquaredSum));
}


double **getDissimilarityMatrix(SERVER *server){

    double **matrix = malloc(server->numberOfTracks * sizeof(double *));

    for(int i = 0; i < server->numberOfTracks; i++)
        matrix[i] = calloc(server->numberOfTracks, sizeof(double));

    for(int i = 0; i < server->numberOfTracks - 1; i++){
        TRACK *track1 = server->tracks[i];
        for(int j = i+1; j < server->numberOfTracks; j++){
            TRACK *track2 = server->tracks[j];
            matrix[i][j] = getDistance(track1, track2);
            matrix[j][i] = matrix[i][j];    
        }
    }

    return(matrix);
}


ARTIST *loadArtistFromCsvRegister(SERVER *server, REGISTER *reg, bool *newFlag){

    ARTIST *artist = serverGetArtist(server, reg->artistId);
    
    if(artist == NULL){
        artist = artistAlocate();
        artistSetName(artist, reg->artistName);
        artistSetId(artist, reg->artistId);
        *newFlag = True;
    }
    else{
        free(reg->artistName);
    }

    return(artist);
}


ALBUM *loadAlbumFromCsvRegister(SERVER *server, REGISTER *reg, bool *newFlag){

    ALBUM *album = serverGetAlbum(server, reg->albumId);

    if(album == NULL){
        album = albumAlocate();
        albumSetName(album, reg->albumName);
        albumSetId(album, reg->albumId);
        *newFlag = True;
    }
    else{
        free(reg->albumName);
    }

    return(album);
}


TRACK *loadTrackFromCsvRegister(SERVER *server, REGISTER *reg, bool *newFlag){

    TRACK *track = serverGetTrack(server, reg->trackId);

    if(track == NULL){
        track = trackALocate();
        trackSetName(track, reg->trackName);
        trackSetId(track, reg->trackId);
        trackSetAlbumId(track, reg->albumId);
        trackSetArtistId(track, reg->artistId);
        trackSetReleaseDate(track, reg->releaseDate);
        trackSetLenght(track, reg->lenght);
        trackSetPopularity(track, reg->popularity);
        trackSetAcousticness(track, reg->acousticness);
        trackSetDanceability(track, reg->danceability);
        trackSetEnergy(track, reg->energy);
        trackSetInstrumentalness(track, reg->instrumentalness);
        trackSetLiveness(track, reg->liveness);
        trackSetLoudness(track, reg->loudness);
        trackSetSpeechness(track, reg->speechness);
        trackSetTime(track, reg->time);
        trackSetTimeSignature(track, reg->timeSignature);
        *newFlag = True;
    }
    else{
        free(reg->trackName);
        free(reg->trackId);
        free(reg->albumId);
        free(reg->artistId);
        free(reg->releaseDate);
    }

    return(track);
}


void serverLoadFromCsvFile(SERVER *server, char *fileName){

    CSV *csvData = csvReadData(fileName);
        
    if(csvData != NULL){
        for(int i = 0; i < csvData->numberOfRegisters; i++){            
            
            bool newArtistFlag = False, newAlbumFlag = False, newTrackFlag = False;
            
            TRACK *track = loadTrackFromCsvRegister(server, csvData->registers[i], &newTrackFlag);
            ALBUM *album = loadAlbumFromCsvRegister(server, csvData->registers[i], &newAlbumFlag);
            ARTIST *artist = loadArtistFromCsvRegister(server, csvData->registers[i], &newArtistFlag);
            
            if(newTrackFlag == True){
                serverInsertTrack(server, track);
                artistSetNumberOfTracks(artist, artistGetNumberOfTracks(artist) + 1);
                albumSetNumberOfTracks(album, albumGetNumberOfTracks(album) + 1); 
            }

            if(newAlbumFlag == True){
                serverInsertAlbum(server, album);
                artistSetNumberOfAlbums(artist, artistGetNumberOfAlbums(artist) + 1);
            }

            if(newArtistFlag == True){
               serverInsertArtist(server, artist); 
            }

            free(csvData->registers[i]);
        }

        for(int i = 0; i < server->numberOfArtists; i++)
            artistSetPopularity(server->artists[i], getArtistPopularity(server, server->artists[i]));

        server->dissimilarityMatrix = getDissimilarityMatrix(server);

        for(int i = 0; i < csvData->header->numberOfFields; i++)
            free(csvData->header->fieldNames[i]);

        free(csvData->header->fieldNames);
        free(csvData->header);
        free(csvData->registers);
        free(csvData);
    }
}


void mergeSortArtistsByPopularity(ARTIST **artists, int startPos, int endPos){

    if(startPos >= endPos) return;

    int centerPos = (startPos + endPos) / 2;

    mergeSortArtistsByPopularity(artists, startPos, centerPos);
    mergeSortArtistsByPopularity(artists, centerPos+1, endPos);

    ARTIST **aux = malloc((endPos-startPos+1) * sizeof(ARTIST *));

    int i = startPos, j = centerPos+1, k = 0;
    
    while(i <= centerPos && j <= endPos){
        if(artistGetPopularity(artists[i]) >= artistGetPopularity(artists[j]))
            aux[k++] = artists[i++];
        else
            aux[k++] = artists[j++];
    }

    while(i <= centerPos)
        aux[k++] = artists[i++];

    while(j <= endPos)
        aux[k++] = artists[j++];

    for(int i = startPos, k = 0; i <= endPos; i++, k++)
        artists[i] = aux[k];

    free(aux);
}


void serverPrintArtistsByPopularity(SERVER *server){

    checkServerContent(server);

    ARTIST **artistsCopy = malloc(server->numberOfArtists * sizeof(ARTIST *));

    for(int i = 0; i < server->numberOfArtists; i++)
        artistsCopy[i] = server->artists[i];

    mergeSortArtistsByPopularity(artistsCopy, 0, server->numberOfArtists-1);    

    printf("Os artistas mais populares sao:\n");
    for(int i = 0; i < server->numberOfArtists; i++){
        printf("(%d) Artista: %s, ", i+1, artistGetName(artistsCopy[i]));
        printf("Musicas: %d musicas, ", artistGetNumberOfTracks(artistsCopy[i]));
        printf("Popularidade: %.2lf, ", artistGetPopularity(artistsCopy[i])); 
        printf("Link: https://open.spotify.com/artist/%s\n", artistGetId(artistsCopy[i]));
    }

    free(artistsCopy);
}


DISSIMILARITY_LINE *getDissimilarityLineSorted(double *originalDistances, int numberOfTrakcs){

    DISSIMILARITY_LINE *trackDissimilarity = malloc(sizeof(DISSIMILARITY_LINE));
    DISSIMILARITY_LINE *trackDissimilarityCopy = malloc(sizeof(DISSIMILARITY_LINE));

    trackDissimilarity->line = malloc(numberOfTrakcs * sizeof(DISSIMILARITY *));
    trackDissimilarityCopy->line = malloc(numberOfTrakcs * sizeof(DISSIMILARITY *));

    for(int i = 0; i < numberOfTrakcs; i++){
        trackDissimilarity->line[i] = malloc(sizeof(DISSIMILARITY));
        trackDissimilarityCopy->line[i] = malloc(sizeof(DISSIMILARITY));
        trackDissimilarity->line[i]->distance = originalDistances[i];
        trackDissimilarity->line[i]->trackIndex = i;
    }

    int *counting = calloc(256, sizeof(int));
    int *accumulated = calloc(256, sizeof(int));

    for(int shift = 0; shift <= 24; shift += 8){
        for(int i = 0; i < numberOfTrakcs; i++){
            int k = ((int) round(trackDissimilarity->line[i]->distance * DISCREETZATION_FACTOR) >> shift) & 255;
            counting[k] += 1;
            trackDissimilarityCopy->line[i]->distance = trackDissimilarity->line[i]->distance;
            trackDissimilarityCopy->line[i]->trackIndex = trackDissimilarity->line[i]->trackIndex;
        }
        accumulated[0] = 0;
        for(int i = 1; i < 256; i++){
            accumulated[i] = accumulated[i-1] + counting[i-1];
            counting[i-1] = 0;
        }
        for(int i = 0; i < numberOfTrakcs; i++){
            int k = ((int) round(trackDissimilarityCopy->line[i]->distance * DISCREETZATION_FACTOR) >> shift) & 255;
            trackDissimilarity->line[ accumulated[k] ]->distance = trackDissimilarityCopy->line[i]->distance;
            trackDissimilarity->line[ accumulated[k] ]->trackIndex = trackDissimilarityCopy->line[i]->trackIndex;
            accumulated[k] += 1;
        }
    }

    for(int i = 0; i < numberOfTrakcs; i++)
        free(trackDissimilarityCopy->line[i]);
    
    free(trackDissimilarityCopy->line); 
    free(trackDissimilarityCopy);
    free(counting);
    free(accumulated);

    return(trackDissimilarity);
}


void serverPrintMostSimilarTracks(SERVER *server, char *trackId, int numberOfSimilar){

    checkServerContent(server);    
    
    int trackIndex = trackBinarySearch(server, trackId);
    
    if(trackIndex != NOT_FOUND){

        double *originalDistances = server->dissimilarityMatrix[trackIndex];

        DISSIMILARITY_LINE *trackDissimilarity = getDissimilarityLineSorted(originalDistances, server->numberOfTracks);                
        int *similarTrackIndexes = malloc(server->numberOfTracks * sizeof(int));
        double *sortedDistances = malloc(server->numberOfTracks * sizeof(double));

        for(int i = 0; i < server->numberOfTracks; i++){
            similarTrackIndexes[i] = trackDissimilarity->line[i]->trackIndex;
            sortedDistances[i] = trackDissimilarity->line[i]->distance;
            free(trackDissimilarity->line[i]);
        }
        free(trackDissimilarity->line);
        free(trackDissimilarity);

        printf("----As %d musicas mais parecidas com %s sao:\n", numberOfSimilar, trackGetName(server->tracks[trackIndex]));
        for(int i = 0; i < numberOfSimilar; i++){
            TRACK *similarTrack = server->tracks[similarTrackIndexes[i]];
            char *artistId = trackGetArtistId(similarTrack);
            ARTIST *artist = serverGetArtist(server, artistId);
            char *artistName = artistGetName(artist);
            printf("\t(%d)Artista: %s\n", i, artistName);
            printf("\t\tMusica: %s\n", trackGetName(similarTrack));
            printf("\t\tDissimilaridade: %lf\n", sortedDistances[i]);
            printf("\t\tLink: https://open.spotify.com/track/%s\n", trackGetId(similarTrack));
        }
        printf("\n");

        free(similarTrackIndexes);
        free(sortedDistances);
    }
}


int serverGetNumberOfArtists(SERVER *server){

    checkServerContent(server);

    return(server->numberOfArtists);
}


int serverGetNumberOfAlbums(SERVER *server){

    checkServerContent(server);

    return(server->numberOfAlbums);
}


int serverGetNumberOfTracks(SERVER *server){

    checkServerContent(server);

    return(server->numberOfTracks);
}