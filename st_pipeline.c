#include "st_pipeline.h"

int main(int argc, char *argv[])
{
	if ((argc < 2) || (argc > 3))
	{
		printf("usage: ./st_pipline N <SEED>\n");
		exit(1);
	}

	srand((argc > 2) ? atoi(argv[2]) : time(NULL)); // seed the random number generator

	int N = (argc > 1) ? atoi(argv[1]) : 10; // number of tasks to be executed
	//defualt value is 10 if no argument is passed

	// Create the active objects
	ActiveObject *active_object1 = CreateActiveObject(Task2);
	ActiveObject *active_object2 = CreateActiveObject(Task3);
	ActiveObject *active_object3 = CreateActiveObject(Task4);

	active_object1->next = active_object2;
	active_object2->next = active_object3;

	for (int i = 0; i < N; i++)
	{
		unsigned int *num = (unsigned int *)malloc(sizeof(unsigned int));
		*num = rand() % 900000 + 100000; // generate a random number between 100000 and 999999

		enQ(getQueue(active_object1), num); // enqueue the number to the first queue
		sleep(1); // sleep for 1 second
	}
	sleep(2); // sleep for 2 seconds
	stop(active_object1); // stop the active objects
	stop(active_object2);
	stop(active_object3);

	return 0;
}

void Task2(void *n, ActiveObject *next)
{
	unsigned int num = *((unsigned int *)n); // get the number from the task
	printf("%u\n", num);					 // print the number
	if (isPrime(num))						 // check if the number is prime
	{
		printf("true\n");
	}
	else
	{
		printf("false\n");
	}
	num += 11; // add 11 to the number

	if (next) // if there is a next active object
	{
		unsigned int *number = (unsigned int *)malloc(sizeof(unsigned int)); // next number to be processed by the next active object
		*number = num;
		enQ(getQueue(next), number); // enqueue the number to the next queue
	}
}

void Task3(void *n, ActiveObject *next)
{
	unsigned int num = *((unsigned int *)n); // get the number from the task
	printf("%u\n", num);					 // print the number
	if (isPrime(num))						 // check if the number is prime
	{
		printf("true\n");
	}
	else
	{
		printf("false\n");
	}

	num -= 13; // subtract 13 from the number

	if (next) // if there is a next active object
	{
		unsigned int *number = (unsigned int *)malloc(sizeof(unsigned int)); // next number to be processed by the next active object
		*number = num;														 // set the next number to the current number
		enQ(getQueue(next), number);										 // enqueue the number to the next queue
	}
}

void Task4(void *n, ActiveObject *next)
{
	unsigned int num = *((unsigned int *)n); // get the number from the task
	printf("%u\n", num);					 // print the number
	if (isPrime(num))						 // check if the number is prime
	{
		printf("true\n");
	}
	else
	{
		printf("false\n");
	}
	num += 2;			 // add 2 to the number
	printf("%u\n", num); // print the number
}
