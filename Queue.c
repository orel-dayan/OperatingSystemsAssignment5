#include "Queue.h"

pQueue createQ()
{
	pQueue newQueue = (pQueue)malloc(sizeof(Queue));
	if (newQueue == NULL)
	{
		printf("malloc failed\n");
		return NULL;
	}
	newQueue->size = 0;
	newQueue->head = NULL;
	newQueue->tail = NULL;
	pthread_cond_init(&newQueue->condition_var, NULL);
	pthread_mutex_init(&newQueue->queue_mutex, NULL);
	return newQueue;
}

void enQ(pQueue queue, void *data)
{
	pthread_mutex_lock(&queue->queue_mutex);
	pNode tmp = (pNode)malloc(sizeof(Node));
	if (tmp == NULL)
	{
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	tmp->element = data;
	tmp->next = NULL;

	if (queue->size == 0) // if the queue is empty
	{
		queue->head = tmp; // the head and the tail are the new node
		queue->tail = tmp; // the head and the tail are the new node
	}
	else // if the queue is not empty
	{
		queue->tail->next = tmp;
		queue->tail = tmp;
	}
	queue->size++;

	pthread_cond_signal(&queue->condition_var); // signal that the queue is not empty
	pthread_mutex_unlock(&queue->queue_mutex);	// unlock the mutex
}

void *deQ(pQueue queue)
{
	pthread_mutex_lock(&queue->queue_mutex); // lock the mutex
	while (isEmpty(queue))					 // if the queue is empty - wait for someone to signal the queue is not empty
	{
		// wait for someone to signal the queue is not empty
		pthread_cond_wait(&queue->condition_var, &queue->queue_mutex);
	}
	pNode tmp = queue->head; // the node we want to delete
	queue->head = tmp->next;
	void *element = tmp->element;
	free(tmp);
	queue->size--; // decrease the size of the queue

	pthread_mutex_unlock(&queue->queue_mutex); // unlock the mutex
	return element;
}

void destoryQ(pQueue queue)
{

	pthread_mutex_lock(&queue->queue_mutex);
	pNode tmp; // temp node
	while (queue->head != NULL)
	{
		tmp = queue->head;
		queue->head = tmp->next;
		free(tmp->element);
		free(tmp);
	}
	pthread_cond_destroy(&queue->condition_var); // destroy the condition variable
	pthread_mutex_destroy(&queue->queue_mutex);	 // destroy the mutex
	pthread_mutex_unlock(&queue->queue_mutex);	 // unlock the mutex
	free(queue);								 // free the queue
}

int isEmpty(pQueue queue)
{
	return queue->size == 0; // return 1 if the queue is empty
}
