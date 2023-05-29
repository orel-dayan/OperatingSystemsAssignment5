#include "ActiveObject.h"

ActiveObject *CreateActiveObject(void (*func)(void *, ActiveObject *))
{
	ActiveObject *activeobject = (ActiveObject *)malloc(sizeof(ActiveObject)); // Allocate memory for the active object
	if (activeobject == NULL)
	{
		printf("Error allocating memory\n");
		exit(1);
	}
	activeobject->queue = createQ(); // Create a queue for the active object
	activeobject->next = NULL;		 // Set the next active object to NULL
	activeobject->func = func;		 // Set the function pointer to the function passed as an argument
	if (pthread_create(&activeobject->thread, NULL, (void *(*)(void *))run, (void *)activeobject) != 0)
	{
		printf("Error creating thread\n");
	}

	return activeobject;
}

void run(ActiveObject *this)
{
	void *task;								  // Task to be executed
	while ((task = deQ(this->queue)) != NULL) // Dequeue a task from the queue
	{
		this->func(task, this->next);
		free(task); // Free the memory allocated for the task
	}
}

Queue *getQueue(ActiveObject *this)
{
	return this->queue;
}

void stop(ActiveObject *this)
{
	pthread_cancel(this->thread); // Cancel the thread
	free(this->queue);			  // Free the memory allocated for the queue
	free(this);					  // Free the memory allocated for the active object
}
