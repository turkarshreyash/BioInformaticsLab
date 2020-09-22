#include <features.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
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
    if (argc < 2 || argc > 2) {
        ERROR("Incorrect Number Of Arguments");
        exit(0);
    }
    char* fileName = args[1];
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
    

    INFO("Starting");

    char fchar;
    int arr[26];
    memset(arr,0,sizeof(int)*26);
    for (ll fp = 0; fp < lenghtOfFile;fp++) {
        fchar = fgetc(file);
        arr[fchar-'A']++;
    }
    OUT("A: %d",arr['A'-'A']);
    OUT("C: %d",arr['C'-'A']);
    OUT("G: %d",arr['G'-'A']);
    OUT("T: %d",arr['T'-'A']);
    
    INFO("Terminated");
}
