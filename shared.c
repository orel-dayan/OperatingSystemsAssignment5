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


int Task1(void *data)
{
    usleep(1000);
    return rand() % 900000 + 100000;
}
int Task2(void *data)
{
    int number = (int)data;
    printf("%d\n",number);
    if(isPrime(number))
        printf("true\n");
    else
        printf("false\n");
    return number+11;
}
int Task3(void *data)
{
    int number = (int)data;
    printf("%d\n",number);

    if(isPrime(number))
        printf("true\n");
    else
        printf("false\n");
    return number-13;
}
int Task4(void *data)
{
    int number = (int)data;
    printf("%d\n",number);
    number+=2;
    printf("%d\n",number);

    return 0;
}
