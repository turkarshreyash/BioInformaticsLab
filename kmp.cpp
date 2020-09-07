#include <iostream>
#include <inttypes.h>
#include <cstring>
#include <string.h>
#include <vector>

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

/**
 * @brief takes a pattern, predefine array and len of pattern as input
 *        computes lps and stores in lps passed as parameter.
 * 
 * @param pattern 
 * @param lps 
 * @param lenOfPattern 
 */
void generateLPS(char *pattern, int *lps, int lenOfPattern)
{
    lps[0] = 0;

    int prevLpsLen = 1;
    int index = 0;

    while (index < lenOfPattern)
    {
        if (pattern[prevLpsLen] == pattern[index])
        {
            prevLpsLen++;
            lps[index] = prevLpsLen;
            index++;
        }
        else
        {
            if (prevLpsLen == 0)
            {
                lps[index] = 0;
                index++;
            }
            else
            {
                prevLpsLen = lps[prevLpsLen - 1];
            }
        }
    }
    return;
}

int main(int argc, char *args[])
{
    if (argc < 3 || argc > 3)
    {
        ERROR("Incorrect Number Of Arguments");
        exit(0);
    }
    char *fileName = args[2];
    INFO("Opening File %s", fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        ERROR("Can't open %s", fileName);
        exit(0);
    }
    SUCCESS("Opened File %s", fileName);
    fseek(file, 0, SEEK_END);
    int lenghtOfFile = ftell(file);
    INFO("Lenght Of File: %intd", lenghtOfFile);
    fseek(file, 0, SEEK_SET);
    char *pattern = args[1];
    int lenghtOfPatttern = strlen(pattern);
    INFO("Patter: %s", pattern);
    INFO("Pattern Lenght: %d", lenghtOfPatttern);
    INFO("Computing LPS");
    int *lps = new int[lenghtOfPatttern];
    generateLPS(pattern, lps, lenghtOfPatttern);
    SUCCESS("Computed LPS");
    int patternFound;
    char fchar;
    INFO("Starting KMP Pattern Match");
    int pp;
    for (int fp = 0; fp <= lenghtOfFile - lenghtOfPatttern;)
    {
        fchar = fgetc(file);
        patternFound = 1;

        for (pp = 0; pp < lenghtOfPatttern; pp++)
        {
            if (fchar != pattern[pp])
            {
                patternFound = 0;
                break;
            }
            fchar = fgetc(file);
        }

        if (patternFound == 1)
        {
            OUT("Pattern Found At %d", fp);
            fp += lenghtOfPatttern;
        }
        else
        {
            // fp++;
            fp += lps[pp];
            fseek(file, fp, SEEK_SET);
        }
    }
    INFO("KMP Pattern Search Terminated");
}