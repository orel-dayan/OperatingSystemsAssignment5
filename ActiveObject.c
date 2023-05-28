#include "ActiveObject.h"
#include "shared.h"

void *run(void *this)
{

	pActiveObject pactiveobject = (pActiveObject)this;
	void *data;	  // the data that we will send to the function
	int res;	  // the result of the function
	int flag = 0; // flag to check if we done check all the data
	while (!flag) // while we didn't check all the data
	{
		if (pactiveobject->func != Task1)	  // if the function is not Task1
			data = deQ(pactiveobject->queue); // get the data from the queue

		if (pactiveobject->func != NULL) // if the function is not NULL
		{
			res = pactiveobject->func(data);
			if (pactiveobject->next)
				enQ(pactiveobject->next->queue, (void *)res);
		}
		pactiveobject->n--; // decrease the number of data that we need to check

		if (0 == pactiveobject->n) // if we done check all the data
			flag = 1;
	}
	return NULL;
}

pActiveObject CreateActiveObject(void(func)(void *), size_t n)
{
	pActiveObject pactiveobject = (pActiveObject)malloc(sizeof(ActiveObject));

	if (pactiveobject == NULL)
	{
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}

	pactiveobject->queue = createQ();

	if (pactiveobject->queue == NULL)
	{
		printf("Error creating queue\n");
		free(pactiveobject);
		exit(EXIT_FAILURE);
	}

	pactiveobject->func = func;
	pactiveobject->n = n;
	pactiveobject->next = NULL;
	pactiveobject->thread = (pthread_t *)calloc(1, sizeof(pthread_t));
	if (pactiveobject->thread == NULL) // if the calloc failed
	{
		printf("calloc failed\n");
		destoryQ(pactiveobject->queue);
		free(pactiveobject);
		exit(EXIT_FAILURE);
	}
	if (pthread_create(pactiveobject->thread, NULL, run, pactiveobject) != 0) // if the pthread_create failed
	{
		printf("pthread_create failed\n");
		// destoryQ(pactiveobject->queue);
		// free(pactiveobject->thread);
		// free(pactiveobject);
		// exit(EXIT_FAILURE);
	}

	return pactiveobject;
}

pQueue getQueue(pActiveObject pactiveobject)
{
	return pactiveobject->queue;
}

void stop(pActiveObject pactiveobject)
{

	pthread_cancel(*pactiveobject->thread); // cancel the thread
	//pthread_join(*pactiveobject->thread, NULL); // wait for the thread to finish
	destoryQ(pactiveobject->queue);			// free the queue
	free(pactiveobject);					// free the active object
}
