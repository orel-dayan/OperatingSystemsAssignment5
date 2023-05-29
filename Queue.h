#pragma once

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Node structure for the queue.
 * value: Pointer to the value of the node.
 * next: Pointer to the next node.
 */

typedef struct Node
{
	void *value;
	struct Node *next;
} Node;

/**
 * @brief Queue structure for the active object.
 * head: Pointer to the head of the queue.
 * tail: Pointer to the tail of the queue.
 * queue_mutex: Mutex for the queue.
 * condition_var: Condition variable for the queue.
 *
 */

typedef struct Queue
{
	Node *head, *tail;
	pthread_mutex_t queue_mutex;
	pthread_cond_t condition_var;
} Queue;

/**
 * @brief Create a queue object and return a pointer to it.
 *
 * @return Queue* Pointer to the created queue.
 */
Queue *createQ();

/**
 * @brief  Add an item to the queue.
 *
 */
void enQ(Queue *, void *);

/**
 * @brief Remove an item from the queue.
 *
 * @return void*
 */
void *deQ(Queue *);
