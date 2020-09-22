#include <iostream>
#include <inttypes.h>
#include <cstring>
#include <string.h>
#include <chrono>
#include <vector>
#include <set>

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
    if (argc < 4 || argc > 4)
    {
        ERROR("Incorrect Number Of Arguments");
        exit(0);
    }
    char *fileName = args[3];
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
    INFO("Lenght Of File: %d", lenghtOfFile);
    fseek(file, 0, SEEK_SET);
    char *pattern = args[1];
    char *pattern2 = args[2];
    int lenghtOfPatttern = strlen(pattern);
    INFO("Patter: %s", pattern);
    INFO("Pattern Lenght: %d", lenghtOfPatttern);
    int lenghtOfPatttern2 = strlen(pattern2);
    INFO("Patter: %s", pattern2);
    INFO("Pattern Lenght: %d", lenghtOfPatttern2);
    INFO("Computing LPS");
    int *lps = new int[lenghtOfPatttern];
    generateLPS(pattern, lps, lenghtOfPatttern);
    int *lps2 = new int[lenghtOfPatttern2];
    generateLPS(pattern2, lps2, lenghtOfPatttern2);
    SUCCESS("Computed LPS");
    int patternFound;
    char fchar;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> found1;
    std::vector<int> found2;
    INFO("Starting KMP Pattern Match For Pattern1");
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
            OUT("Pattern1 Found At %d", fp);
            found1.push_back(fp);
            fp += lenghtOfPatttern;
        }
        else
        {
            fp ++;
            fseek(file, fp, SEEK_SET);
        }
    }

    INFO("Starting KMP Pattern Match For Pattern2");
    fseek(file, 0, SEEK_SET);
    for (int fp = 0; fp <= lenghtOfFile - lenghtOfPatttern2;)
    {
        fchar = fgetc(file);
        patternFound = 1;

        for (pp = 0; pp < lenghtOfPatttern2; pp++)
        {
            if (fchar != pattern2[pp])
            {
                patternFound = 0;
                break;
            }
            fchar = fgetc(file);
        }

        if (patternFound == 1)
        {
            OUT("Pattern2 Found At %d", fp);
            found2.push_back(fp);
            fp += lenghtOfPatttern2;
        }
        else
        {
            fp++;
            // fp += lps2[pp];
            fseek(file, fp, SEEK_SET);
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    INFO("KMP Pattern Search Terminated: %ld", duration.count());
    INFO("Starting Overlap Searching");
    int startsAt1, endsAt1, startsAt2, endsAt2;
    int index1 = 0, index2 = 0;
    if (found1.size() < 0 && found2.size() < 0)
    {
        OUT("No Over Lapping");
        exit(0);
    }

    while (index1 < found1.size() && index2 < found2.size())
    {
        startsAt1 = found1[index1];
        startsAt2 = found2[index2];
        endsAt1 = startsAt1 + lenghtOfPatttern;
        endsAt2 = startsAt2 + lenghtOfPatttern;
        if (startsAt1 <= startsAt2)
        {
            if (endsAt1 < startsAt2)
            {
                // index1++;
            }
            else
            {
                OUT("Overlap at P1:%d, P2:%d", startsAt1, startsAt2);
            }
            index1++;
        }
        else
        {
            if (endsAt2 < startsAt1)
            {
                // index2++;
            }
            else
            {
                OUT("Overlap at P1:%d, P2:%d", startsAt1, startsAt2);
            }
            index2++;
        }
    }
    INFO("Overlap Search Complete");

}