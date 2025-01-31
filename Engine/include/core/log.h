#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

void log_success(char* message);
void log_info(char* message);
void log_error(char* message);

#endif /* LOG_H */
