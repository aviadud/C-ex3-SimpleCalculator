/**
 * @file queue.c
 * @author Aviad Dudkevich
 *
 * @brief Implementation of a queue data structure.
 */

#include "queue.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief Initiate an queue.
 * @param elementSize - the size of the data in all the nodes.
 * @return a pinter to the queue.
 */
Queue* queueAlloc(size_t elementSize)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        return NULL;
    }
    queue->_head = NULL;
    queue->_tail = NULL;
    queue->_elementSize = elementSize;
    return queue;
}

/**
 * @brief free all memory the stack used.
 * @param queue - a pointer to pointer of the queue.
 */
void freeQueue(Queue** queue)
{
    QueueNode* p1;
    QueueNode* p2;
    if (*queue != NULL)
    {
        p1= (*queue)->_head;
        while(p1)
        {
            p2= p1;
            p1= p1->_next;
            free(p2->_data);
            free(p2);
        }
        free(*queue);
        *queue = NULL;
    }
}

/**
 * @brief put new data un queue.
 * @param queue - a pointer to the queue.
 * @param data - a pointer to the data.
 * @param dataTypeFlag - an integer to represent the data type.
 */
void enqueue(Queue* queue, void *data, int dataTypeFlag)
{
    //you should check allocation success
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node == NULL)
    {
        fprintf(stderr, "Memory error - enqueue filed.\n");
        return;
    }
    node->_data = malloc(queue->_elementSize);
    if (node->_data == NULL)
    {
        fprintf(stderr, "Memory error - enqueue filed.\n");
        return;
    }
    node->_dataTypeFlag = dataTypeFlag;
    memcpy(node->_data, data, queue->_elementSize);
    node->_next = NULL;
    if (queue->_head == NULL)
    {
        queue->_head = node;
    }
    else
    {
        queue->_tail->_next = node;
    }
    queue->_tail = node;
}

/**
 * @brief pop the data from the end of the queue.
 * @param queue - a pointer to the queue.
 * @param headData - - a pointer to save the data on.
 * @return integer represent the data type.
 */
int dequeue(Queue* queue, void *headData)
{
    if(queue->_head == NULL)
    {
        fprintf(stderr, "The queue is empty\n");
        return 0;
    }
    QueueNode *node = queue->_head;
    int dataFlagType = node->_dataTypeFlag;
    memcpy(headData, node->_data, queue->_elementSize);
    queue->_head = node->_next;
    free(node->_data);
    free(node);
    return dataFlagType;
}

/**
 * @brief check if stack is empty.
 * @param queue - a pointer to the queue.
 * @return true or false.
 */
int isEmptyQueue(Queue* queue)
{
    return queue->_head == NULL;
}