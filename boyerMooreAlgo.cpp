/**
 * @file boyerMooreAlgo.cpp
 * @author Shreyash H. Turkar (turkarshreyash@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-09-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cstring>
#include <chrono>

#define INF __LONG_LONG_MAX__
#define NEG_INF -(INF)
#define ll long long

// mini logger
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

std::vector<ll> badCharShiftPreprocess(std::string p)
{
    char a;
    ll j;
    ll m = p.size();
    std::vector<ll> occ(26);
    for (a = 0; a < 26; a++)
        occ[a] = -1;

    for (j = 0; j < m; j++)
    {
        a = p[j];
        occ[a] = j;
    }
    return occ;
}

void goodSuffixPre1(std::string p, std::vector<ll> s, std::vector<ll> f)
{
    ll m = p.size();
    ll i = m, j = m + 1;
    f[i] = j;
    while (i > 0)
    {

        while (j <= m && p[i - 1] != p[j - 1])
        {

            if (s[j] == 0)
                s[j] = j - i;
            j = f[j];
        }
        i--;
        j--;
        f[i] = j;
    }
}

void goodSuffixPre2(std::string p, std::vector<ll> s, std::vector<ll> f)
{
    ll m = p.size();
    ll i, j;
    j = f[0];
    for (i = 0; i <= m; i++)
    {
        if (s[i] == 0)
            s[i] = j;
        if (i == j)
            j = f[j];
    }
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
    std::string pattern = args[1];
    int lenghtOfPatttern = pattern.size();
    // INFO("Patter: %s", pattern.c);
    INFO("Pattern Lenght: %d", lenghtOfPatttern);
    INFO("Preprocessing");
    std::vector<ll> f(lenghtOfPatttern + 2);
    std::vector<ll> s(lenghtOfPatttern + 2);
    INFO("Preprocessing: BadSuffix");
    std::vector<ll> occ = badCharShiftPreprocess(pattern);
    SUCCESS("BadSuffix Completed");
    INFO("Preprocessing: GoodSuffix");
    goodSuffixPre1(pattern, s, f);
    SUCCESS("GoodSuffix Preprocess 1 Completed");
    INFO("Preprocessing 2: GoodSuffix");
    goodSuffixPre2(pattern, s, f);
    SUCCESS("GoodSuffix Preprocess 2 Completed");
    int patternFound;
    char fchar;
    auto start = std::chrono::high_resolution_clock::now();
    INFO("Starting Boyer Moore Pattern Match:");
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
            // OUT("Pattern Found At %d", fp);
            fp += lenghtOfPatttern;
        }
        else
        {
            // fp++;
            fp += std::max(s[pp + 1], pp - occ[fchar - 65]);
            fseek(file, fp, SEEK_SET);
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    INFO("BoyerMoore Pattern Search Terminated: %ld", duration.count());
}