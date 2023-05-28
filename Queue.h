#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct _Node
{
	void *element;
	struct _Node *next;
} Node, *pNode;

typedef struct _Queue
{
	pNode head;
	pNode tail;
	size_t size;
	pthread_cond_t condition_var;
	pthread_mutex_t queue_mutex;
} Queue, *pQueue;

pQueue createQ();

int isEmpty(pQueue queue);

void enQ(pQueue queue, void *data);

void *deQ(pQueue queue);

void destoryQ(pQueue queue);
