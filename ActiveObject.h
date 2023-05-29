#pragma once

#include "Queue.h"

typedef struct ActiveObject ActiveObject;

struct ActiveObject
{
	pthread_t thread;
	Queue *queue;
	ActiveObject *next;
	void (*func)(void *, ActiveObject *);
};

/**
 * @brief Create a Active Object object and return a pointer to it.
 *
 * @param func Function pointer to the function to be executed by the active object.
 * @return ActiveObject* Pointer to the created active object.
 */

ActiveObject *CreateActiveObject(void (*func)(void *, ActiveObject *));

/**
 * @brief Main loop of the active object.
 */

void run(ActiveObject *);

/**
 * @brief Get the Queue object of the active object.
 *
 * @return Queue* Pointer to the queue of the active object.
 */

Queue *getQueue(ActiveObject *);

/**
 * @brief Stop the active object.
 */

void stop(ActiveObject *);
