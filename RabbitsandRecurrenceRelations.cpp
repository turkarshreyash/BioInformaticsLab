#include <iostream>
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

int main(int argc, char *args[])
{
    if (argc < 3 || argc > 3)
    {
        ERROR("Incorrect Number Of Arguments");
        exit(0);
    }
    int n = atoi(args[1]);
    int k = atoi(args[2]);
    int *arr = new int[n+1];
    arr[0] = 1;
    arr[1] = 1;
    arr[2] = 1;
    /*
    0 1 2 3 4 5
    1 1 1 
    */
    for(int i = 3; i <= n ; i++){
        arr[i] = arr[i-1]+arr[i-2]*k;
    }
    OUT("After %d months: %d",n,arr[n]);
}