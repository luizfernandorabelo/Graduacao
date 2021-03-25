#ifndef TRACK_H 
    #define TRACK_H

    #define TRACK_ACCESS_FAILURE 0

    typedef struct track_ TRACK;

    TRACK *trackALocate(void);
    void trackFree(TRACK **track);

    void trackSetName(TRACK *track, char *trackName);
    void trackSetId(TRACK *track, char *id);
    void trackSetAlbumId(TRACK *track, char *albumId);
    void trackSetArtistId(TRACK *track, char *artistId);
    void trackSetReleaseDate(TRACK *track, char *releaseDate);
    void trackSetLenght(TRACK *track, int lenght);
    void trackSetPopularity(TRACK *track, int popularity);
    void trackSetAcousticness(TRACK *track, double acousticness);
    void trackSetDanceability(TRACK *track, double danceability);
    void trackSetEnergy(TRACK *track, double energy);
    void trackSetInstrumentalness(TRACK *track, double instrumentalness);
    void trackSetLiveness(TRACK *track, double liveness);
    void trackSetLoudness(TRACK *track, double loudness);
    void trackSetSpeechness(TRACK *track, double speechness);
    void trackSetTime(TRACK *track, double time);
    void trackSetTimeSignature(TRACK *track, int timeSignature);

    char *trackGetName(TRACK *track);
    char *trackGetId(TRACK *track);
    char *trackGetAlbumId(TRACK *track);
    char *trackGetArtistId(TRACK *track);
    char *trackGetReleaseDate(TRACK *track);
    int trackGetLenght(TRACK *track);
    int trackGetPopularity(TRACK *track);
    double trackGetAcousticness(TRACK *track);
    double trackGetDanceability(TRACK *track);
    double trackGetEnergy(TRACK *track);
    double trackGetInstrumentalness(TRACK *track);
    double trackGetLiveness(TRACK *track);
    double trackGetLoudness(TRACK *track);
    double trackGetSpeechness(TRACK *track);
    double trackGetTime(TRACK *track);
    int trackGetTimeSignature(TRACK *track);

#endif