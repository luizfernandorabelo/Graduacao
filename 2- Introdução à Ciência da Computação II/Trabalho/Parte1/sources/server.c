#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

#define NOT_FOUND -1 


struct server_{
    ARTIST **artists;
    int numberOfArtists;
    int numberOfAlbums;
    int numberOfTracks;
};


SERVER *serverALocate(void){

    SERVER *server = malloc(sizeof(SERVER));

    if(server != NULL){
        server->artists = NULL;
        server->numberOfArtists = 0;
        server->numberOfAlbums = 0;
        server->numberOfTracks = 0;
    }

    return(server);
}


void serverFree(SERVER **server){

    if(*server == NULL)
        return;

    if((*server)->artists != NULL){
        for(int i = 0; i < (*server)->numberOfArtists; i++)
            artistFree(&(*server)->artists[i]);
        free((*server)->artists);
    }

    free(*server);
    *server = NULL;
}


int getArtistInsertionIndex(SERVER *server, char *artistId){

    int index = 0;

    while(index < server->numberOfArtists && strcmp(artistGetId(server->artists[index]), artistId) < 0)
        index += 1;
    
    return(index);
}


void serverInsertArtist(SERVER *server, ARTIST *artist){

    if(server == NULL)
        return;

    server->artists = realloc(server->artists, (server->numberOfArtists+1) * sizeof(ARTIST *));

    int insertionIndex = getArtistInsertionIndex(server, artistGetId(artist));

    for(int i = server->numberOfArtists; i > insertionIndex; i--)
        server->artists[i] = server->artists[i-1];

    server->artists[insertionIndex] = artist;
    server->numberOfArtists += 1;
}


ARTIST *loadArtistFromCsvFile(SERVER *server, REGISTER *reg, bool *newFlag){

    ARTIST *artist = serverGetArtist(server, reg->artistId);
    
    if(artist == NULL){
        artist = artistAlocate();
        artistSetName(artist, reg->artistName);
        artistSetId(artist, reg->artistId);
        *newFlag = True;
    }
    else{
        free(reg->artistName);
        free(reg->artistId);
    }

    return(artist);
}


ALBUM *loadAlbumFromCsvFile(ARTIST *artist, REGISTER *reg, bool *newFlag){

    ALBUM *album = artistGetAlbum(artist, reg->albumId);

    if(album == NULL){
        album = albumAlocate();
        albumSetName(album, reg->albumName);
        albumSetId(album, reg->albumId);
        *newFlag = True;
    }
    else{
        free(reg->albumName);
        free(reg->albumId);
    }

    return(album);
}


TRACK *loadTrackFromCsvFile(ALBUM *album, REGISTER *reg, bool *newFlag){

    TRACK *track = albumGetTrack(album, reg->trackId);

    if(track == NULL){
        track = trackALocate();
        trackSetName(track, reg->trackName);
        trackSetId(track, reg->trackId);
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
        free(reg->releaseDate);
    }

    return(track);
}


void serverLoadFromCsvFile(SERVER *server, char *fileName){

    CSV *csvData = csvReadData(fileName);

    if(csvData == NULL)
        return;
        
    for(int i = 0; i < csvData->numberOfRegisters; i++){            
        
        bool newArtistFlag = False, newAlbumFlag = False, newTrackFlag = False;
        
        ARTIST *artist = loadArtistFromCsvFile(server, csvData->registers[i], &newArtistFlag);
        ALBUM *album = loadAlbumFromCsvFile(artist, csvData->registers[i], &newAlbumFlag);
        TRACK *track = loadTrackFromCsvFile(album, csvData->registers[i], &newTrackFlag);
        
        if(newTrackFlag == True){
            albumInsertTrack(album, track);
            server->numberOfTracks += 1;
        }

        if(newAlbumFlag == True){
            artistInsertAlbum(artist, album);
            server->numberOfAlbums += 1;
        }

        if(newArtistFlag == True){
            serverInsertArtist(server, artist); 
        }

        free(csvData->registers[i]);
    }

    for(int i = 0; i < csvData->header->numberOfFields; i++)
        free(csvData->header->fieldNames[i]);

    free(csvData->header->fieldNames);
    free(csvData->header);
    free(csvData->registers);
    free(csvData);
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


void checkServerContent(SERVER *server){

    if(server == NULL){
        printf("Server access failure! The server points to no content\n");
        exit(SERVER_ACCESS_FAILURE);
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

    #ifdef SERVER_SORTED_BY_ARTIST_ID 
        int index = artistBinarySearch(server, artistId);
        return((index != NOT_FOUND) ? server->artists[index] : NULL);
    #else
        for(int i = 0; i < server->numberOfArtists; i++){
            char *currentId = artistGetId(server->artists[i]);
            if(strcmp(currentId, artistId) == 0)
                return(server->artists[i]);
        }
        return(NULL);
    #endif
}