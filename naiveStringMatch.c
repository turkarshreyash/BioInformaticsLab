#include <features.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

//mini logger
#define ERROR(S, ...)             \
    {                             \
        printf("[ERROR]  ");      \
        printf(S, ##__VA_ARGS__); \
        printf("\n");             \
    }

#define INFO(S, ...)              \
    {                             \
        printf("[INFO]   ");      \
        printf(S, ##__VA_ARGS__); \
        printf("\n");             \
    }

#define SUCCESS(S, ...)           \
    {                             \
        printf("[OK]     ");      \
        printf(S, ##__VA_ARGS__); \
        printf("\n");             \
    }

#define OUT(S, ...)               \
    {                             \
        printf("[OUTPUT] ");      \
        printf(S, ##__VA_ARGS__); \
        printf("\n");             \
    }

int main(int argc, char* args[])
{
    if (argc < 3 || argc > 3) {
        ERROR("Incorrect Number Of Arguments");
        exit(0);
    }
    char* fileName = args[2];
    INFO("Opening File %s", fileName);
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        ERROR("Can't open %s", fileName);
        exit(0);
    }
    SUCCESS("Opened File %s", fileName);
    fseek(file, 0, SEEK_END);
    ll lenghtOfFile = ftell(file);
    INFO("Lenght Of File: %lld", lenghtOfFile);
    fseek(file, 0, SEEK_SET);
    char* pattern = args[1];
    ll lenghtOfPatttern = strlen(pattern);
    INFO("Patter: %s", pattern);
    INFO("Pattern Lenght: %lld", lenghtOfPatttern);

    INFO("Starting Naive Pattern Match");

    int patternFound;
    char fchar;

    for (ll fp = 0; fp <= lenghtOfFile - lenghtOfPatttern;) {
        fchar = fgetc(file);
        patternFound = 1;

        for (ll pp = 0; pp < lenghtOfPatttern; pp++) {
            if (fchar != pattern[pp]) {
                patternFound = 0;
                break;
            }
            fchar = fgetc(file);
        }

        if (patternFound == 1) {
            SUCCESS("Pattern Found At %lld", fp);
            fp += lenghtOfPatttern;
        } else {
            fp++;
            fseek(file, fp, SEEK_SET);
        }
    }
    INFO("Naive Pattern Search Terminated");
}