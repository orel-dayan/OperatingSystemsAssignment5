#include "Queue.h"

Queue *createQ()
{
	Queue *newQ = (Queue *)malloc(sizeof(Queue)); // Allocate memory for the queue
	if (newQ == NULL)
	{
		printf("Error allocating memory\n");
		exit(1);
	}
	newQ->head = newQ->tail = NULL;				   // Initialize the head and tail to NULL
	pthread_mutex_init(&newQ->queue_mutex, NULL);  // Initialize the mutex
	pthread_cond_init(&newQ->condition_var, NULL); // Initialize the condition variable
	return newQ;								   // Return the pointer to the queue
}

void enQ(Queue *queue, void *value)
{
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp->value = value;
	tmp->next = NULL;
	pthread_mutex_lock(&queue->queue_mutex);
	if (queue->tail == NULL) // Queue is empty
	{
		queue->head = queue->tail = tmp;			// Set head and tail to the new node
		pthread_cond_signal(&queue->condition_var); // Signal the condition variable to wake up a thread waiting on it
	}
	else // Queue is not empty
	{
		queue->tail->next = tmp;
		queue->tail = tmp;
	}
	pthread_mutex_unlock(&queue->queue_mutex); // Unlock the mutex to allow other threads to access the queue
}

void *deQ(Queue *queue)
{
	pthread_mutex_lock(&queue->queue_mutex); // Lock the mutex to allow only one thread to access the queue

	while (queue->head == NULL)
	{																   // Queue is empty
		pthread_cond_wait(&queue->condition_var, &queue->queue_mutex); // wait for someone to signal the queue is not empty
	}
	Node *tmp = queue->head; // the node to be removed
	void *value = tmp->value;
	queue->head = queue->head->next;

	if (queue->head == NULL)
	{						// Queue is empty
		queue->tail = NULL; // Set tail to NULL
	}
	pthread_mutex_unlock(&queue->queue_mutex); // Unlock the mutex to allow other threads to access the queue

	free(tmp); // Free the memory allocated for the node

	return value;
}
