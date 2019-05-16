/**
 * @file queue.h
 * @author Aviad Dudkevich
 * @brief header file for queue.c
 */

#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <stdlib.h>

typedef struct QueueNode
{
    void * _data; // pointer to anything
    int _dataTypeFlag; // flag to determine type.
    struct QueueNode * _next;
} QueueNode;

typedef struct Queue
{
    struct QueueNode * _head;
    struct QueueNode * _tail;
    size_t _elementSize;    // we need that for memcpy
} Queue;

Queue* queueAlloc(size_t elementSize);

void freeQueue(Queue** queue);

void enqueue(Queue* queue, void *data, int dataTypeFlag);

int dequeue(Queue* queue, void *headData);

int isEmptyQueue(Queue* queue);



#endif //EX3_QUEUE_H
