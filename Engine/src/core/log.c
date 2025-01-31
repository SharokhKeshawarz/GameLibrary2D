#include "core/log.h"

void log_success(char* message)
{
    time_t now = time(NULL);

    struct tm* local = localtime(&now);
    
    int day = local->tm_mday;
    int month = local->tm_mday + 1;
    int year = local->tm_year + 1900;

    int hour = local->tm_hour;
    int minute = local->tm_min;
    int second = local->tm_sec;

    printf(
        GREEN "[ %d/%d/%d - %02d:%02d:%02d ] -> %s\n" RESET,
        day, month, year, hour, minute, second, message
    );
}

void log_info(char* message)
{
    time_t now = time(NULL);

    struct tm* local = localtime(&now);
    
    int day = local->tm_mday;
    int month = local->tm_mday + 1;
    int year = local->tm_year + 1900;

    int hour = local->tm_hour;
    int minute = local->tm_min;
    int second = local->tm_sec;

    printf(
        BLUE "[ %d/%d/%d - %02d:%02d:%02d ] -> %s\n" RESET,
        day, month, year, hour, minute, second, message
    );
}

void log_error(char* message)
{
    time_t now = time(NULL);

    struct tm* local = localtime(&now);
    
    int day = local->tm_mday;
    int month = local->tm_mday + 1;
    int year = local->tm_year + 1900;

    int hour = local->tm_hour;
    int minute = local->tm_min;
    int second = local->tm_sec;

    printf(
        RED "[ %d/%d/%d - %02d:%02d:%02d ] -> %s\n" RESET,
        day, month, year, hour, minute, second, message
    );
}
