#ifndef STOP_WATCH_H
    #define STOP_WATCH_H

    #include <time.h>

    double getExecutionTime(time_t startTime, time_t endTime);
    void printExecutionTime(double timeTaken);
    
#endif