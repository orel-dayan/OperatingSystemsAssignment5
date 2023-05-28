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
	if (argc == 2) 
	{
		seed = time(NULL);
	}
	else
	{
		seed = atoi(argv[2]);
	}

	srand(seed);
	pActiveObject pactiveobject4 = CreateActiveObject(Task4, NULL, N);
	pActiveObject pactiveobject3 = CreateActiveObject(Task3, pactiveobject4, N);
	pActiveObject pactiveobject2 = CreateActiveObject(Task2, pactiveobject3, N);
	pActiveObject pactiveobject1 = CreateActiveObject(Task1, pactiveobject2, N);

	while (1)
	{
		sleep(1);
		if (!pactiveobject1->n && !pactiveobject2->n && !pactiveobject3->n && !pactiveobject4->n)
		{
			stop(pactiveobject1);
			stop(pactiveobject2);
			stop(pactiveobject3);
			stop(pactiveobject4);
			break;
		}
	}

	return 0;
}
