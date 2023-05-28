#pragma once

#include "Queue.h"

typedef struct _ActiveObject
{
	pthread_t *thread;
	pQueue queue;
	int (*func)(void *);
	struct _ActiveObject *next;
	size_t n;
} ActiveObject, *pActiveObject;

pActiveObject CreateActiveObject(void(func)(void *), size_t n);

pQueue getQueue(pActiveObject this);

void stop(pActiveObject this);

void *run(void *this);
