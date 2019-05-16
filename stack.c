/**
 * @file stack.c
 * @author lab c and aviad dudkevich.
 *
 * @brief Implementation of a stack data structure.
 */

#include "stack.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief Initiate a stack
 * @param elementSize - the size of the data in all the nodes.
 * @return the stack.
 */
Stack* stackAlloc(size_t elementSize)
{
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  if (stack == NULL)
  {
      return NULL;
  }
  stack->_top = NULL;
  stack->_elementSize = elementSize;
  return stack;
}

/**
 * @brief free all memory the stack used.
 * @param stack - a pointer to a pinter of stack.
 */
void freeStack(Stack** stack)
{
  StackNode* p1;
  StackNode* p2;
  if (*stack != NULL)
    {
      p1= (*stack)->_top;
      while(p1)
	{
	  p2= p1;
	  p1= p1->_next;
	  free(p2->_data);
	  free(p2);
	}
      free(*stack);
      *stack = NULL;
    }
}

/**
 * @brief push data to the stack.
 * @param stack - a pointer to the stack.
 * @param data - a pointer to the data.
 */
void push(Stack* stack, void *data)
{
  StackNode* node = (StackNode*)malloc(sizeof(StackNode));
  if (node == NULL)
  {
      fprintf(stderr, "Memory error - push filed.\n");
      return;
  }
  node->_data = malloc(stack->_elementSize);
  if (node->_data == NULL)
  {
      fprintf(stderr, "Memory error - push filed.\n");
      return;
  }
  memcpy(node->_data, data, stack->_elementSize);
  node->_next = stack->_top;
  stack->_top = node;
}

/**
 * @brief peek at the top of the stack (without taking the node out of the stack).
 * @param stack - a pointer to the stack.
 * @param headData - a pointer to save the data on.
 */
void peek(Stack* stack, void *headData)
{
    if(stack->_top == NULL)
    {
        fprintf(stderr, "The stack is empty\n");
        return;
    }
    StackNode *node = stack->_top;
    memcpy(headData, node->_data, stack->_elementSize);
}

/**
 * @brief pop the top of the stack.
 * @param stack - a pointer to the stack.
 * @param headData - a pointer to save the data on.
 */
void pop(Stack* stack, void *headData) 
{
  if(stack->_top == NULL)
    {
      fprintf(stderr, "The stack is empty\n");
      return;
    }
  StackNode *node = stack->_top;
  memcpy(headData, node->_data, stack->_elementSize);
  stack->_top = node->_next;  
  free(node->_data);
  free(node);
}

/**
 * @brief check if stack is empty.
 * @param stack - a pointer to the stack.
 * @return true or false.
 */
int isEmptyStack(Stack* stack) 
{
  return stack->_top == NULL; 
}
