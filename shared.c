#include "shared.h"
#include "Queue.h"
#include "ActiveObject.h"


int isPrime(unsigned int num)
{
    if (num == 0 || num == 1)
    {
        return 0;
    }
    for (int i = 2; i*i < num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int randomInt(int seed)
{
    if (!seed)
    {
        seed = time(0);
    }
    srand(seed);
    int randomNumber = rand() % 900000 + 100000;
    return randomNumber;
}

int Task1(int seed)
{
    int num = randomInt(seed);
    return num;
}

int Task2(int num)
{
    printf("%d\n", num);
    if (isPrime(num))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    num += 11;
    return num;
}

int Task3(int num)
{
    printf("%d\n", num);
    if (isPrime(num))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    num -= 13;
    return num;
}

int Task4(int num)
{
    printf("%d\n", num);
    if (isPrime(num))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    num += 2;
    printf("%d\n", num);
    return num;
}
