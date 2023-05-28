#include "shared.h"
#include "Queue.h"
#include "ActiveObject.h"

int main(int argc, char *argv[])
{
    if ((argc < 2) || (argc > 3))
    {
        printf("usage: ./st_pipline N <SEED>\n");
        exit(1);
    }

    int N = atoi(argv[1]);
    size_t seed;
    if (argc == 2) // if we didn't get seed
    {
        seed = time(NULL);
    }
    else
    {
        seed = atoi(argv[2]);
    }

    srand(seed);


    pActiveObject p1 = CreateActiveObject(Task1, N);
    pActiveObject p2 = CreateActiveObject(Task2, N);
    pActiveObject p3 = CreateActiveObject(Task3, N);
    pActiveObject p4 = CreateActiveObject(Task4, N);


    p1->next = p2;
    p2->next = p3;
    p3->next = p4;
    while (1)
    {
        sleep(1);
        if (!p1->n && !p2->n && !p3->n && !p4->n && isEmpty(p1->queue) && isEmpty(p2->queue) && isEmpty(p3->queue) && isEmpty(p4->queue))
        {
            stop(p1);
            stop(p2);
            stop(p3);
            stop(p4);
            break;
        }
    }
    return 0;
}
