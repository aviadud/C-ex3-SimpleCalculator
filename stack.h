/**
 * @file stack.h
 * @author lab c
 * @brief header file for stack.c
  */
#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct StackNode
{
  void * _data; // pointer to anything
  struct StackNode * _next;
} StackNode;

typedef struct Stack
{
  StackNode * _top;
  size_t _elementSize;    // we need that for memcpy
} Stack;

Stack* stackAlloc(size_t elementSize);

void freeStack(Stack** stack);

void push(Stack* stack, void *data);

void peek(Stack* stack, void *headData);

void pop(Stack* stack, void *headData);

int isEmptyStack(Stack* stack);

#endif
