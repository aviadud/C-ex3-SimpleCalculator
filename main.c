/**
 * @file main.c
 * @author aviad dudkevich
 *
 * @brief Read from stdin arithmetic expression and translated to from infix to postfix and print
 * the result of the expression.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "queue.h"
#include "basicMath.h"

#define MAX_LINE_LENGTH 100

/**
 * constants:
 */
enum Parentheses{LEFT_PARENTHESIS = '(', RIGHT_PARENTHESIS = ')'};
enum DataType{CHAR = 0, INT = 1};
const int BASE10 = 10;
const char MEMORY_ERROR[] = "memory error\n";

/**
 * @brief Aid infixToPostfixConverter function handle operator case.
 * @param operator - pointer to a char.
 * @param processingHelper - the stack that help processing the expression.
 * @param output - the queue of the postfix output.
 */
void operatorHandle(const char * operator, Stack * processingHelper, Queue * output) {

    char tempCharPointer[1] = {'0'};
    if (!isEmptyStack(processingHelper)) {
        peek(processingHelper, tempCharPointer);
    }
    if (isEmptyStack(processingHelper) || *tempCharPointer == LEFT_PARENTHESIS) {
        push(processingHelper, (void *) operator);
    }
    else
    {
        while (!isEmptyStack(processingHelper))
        {
            peek(processingHelper, (void *) tempCharPointer);
            if (*tempCharPointer != LEFT_PARENTHESIS &&
                precedenceOperator(*tempCharPointer, *operator))
            {
                pop(processingHelper, (void *) tempCharPointer);
                enqueue(output, (void *) tempCharPointer, CHAR);
            }
            else
            {
                break;
            }
        }
        push(processingHelper, (void*) operator);
    }
}

/**
 * @brief Takes a input string of infix expression and converting it to postfix expression. While
 * doing that, the function also prints the infix expression. Invalid characters are ignored.
 * @param inputString - the input string of infix expression.
 * @param numbers - an array to help with the conversion.
 * @return a pointer to a queue of postfix expression.
 */
Queue * infixToPostfixConverter(const char inputString[MAX_LINE_LENGTH], int numbers[])
{
    size_t length = strlen(inputString);
    bool isNumber = false;
    int numberIndex = 0, inputIndex = 0;
    char tempCharPointer[1] = {'0'}, * end;
    Queue *output = queueAlloc(sizeof(int));
    Stack *processingHelper = stackAlloc(sizeof(char));
    if (output == NULL || processingHelper == NULL) // check if memory allocation succeeded.
    {
        fprintf(stderr, MEMORY_ERROR);
        exit(EXIT_FAILURE);
    }
    printf("Infix: ");
    while (inputIndex < length)
    {
        switch (inputString[inputIndex])
        {
            case PLUS:
            case MINUS:
            case MULTIPLY:
            case DIVISION:
            case POWER:
                printf("%c ", inputString[inputIndex]);
                operatorHandle(inputString + inputIndex, processingHelper, output);
                break;
            case LEFT_PARENTHESIS:
                printf("%c ", LEFT_PARENTHESIS);
                push(processingHelper, (void*) inputString + inputIndex);
                break;
            case RIGHT_PARENTHESIS:
                printf("%c", RIGHT_PARENTHESIS);
                while (!isEmptyStack(processingHelper))
                {
                    pop(processingHelper, tempCharPointer);
                    if (*tempCharPointer == LEFT_PARENTHESIS)
                    {
                        break;
                    }
                    enqueue(output, tempCharPointer, CHAR);
                }
                break;
            default:
                if ('0' <= inputString[inputIndex] && inputString[inputIndex] <= '9')
                {
                    isNumber = true;
                    numbers[numberIndex] = (int) strtol(inputString + inputIndex, &end, BASE10);
                    printf("%d ", numbers[numberIndex]);
                    enqueue(output, numbers + numberIndex, INT);
                    numberIndex++;
                    inputIndex += (int) (end - inputString - inputIndex);
                }
        }
        if (!isNumber)
        {
            inputIndex++;
        }
        isNumber = false;
    }
    while (!isEmptyStack(processingHelper))
    {
        pop(processingHelper, tempCharPointer);
        enqueue(output, tempCharPointer, CHAR);
    }
    freeStack(&processingHelper);
    printf("\n");
    return output;
}

/**
 * @brief Takes a postfix expression and return the result (in integers) of the expression. Also,
 * prints the the expression.
 * @param postfix - an queue containing postfix expression.
 * @return The result (in integers) of the expression.
 */
int evaluatePostfixExpression(Queue *postfix)
{
    Stack *processingHelper = stackAlloc(sizeof(int));
    if (processingHelper == NULL) // check if memory allocation succeeded.
    {
        fprintf(stderr, MEMORY_ERROR);
        exit(EXIT_FAILURE);
    }
    int type, data[MAX_LINE_LENGTH] = {0}, index = 0, tempA = 0, tempB = 0, output = 0;
    printf("Postfix: ");
    while (!isEmptyQueue(postfix))
    {
        type = dequeue(postfix, data + index);
        switch (type)
        {
            case INT:
                printf("%d ", data[index]);
                push(processingHelper, data + index);
                break;
            case CHAR:
                printf("%c ", data[index]);
                pop(processingHelper, &tempA);
                pop(processingHelper, &tempB);
                data[index] = evaluate(tempA, tempB, (char) data[index]);
                push(processingHelper, data + index);
                break;
        }
        index++;
    }
    printf("\n");
    pop(processingHelper, &output);
    freeStack(&processingHelper);
    return output;
}


/**
 * @brief The main program. Read from stdin arithmetic expression and translated to from infix to
 * postfix and print the result of the expression.
 * @return 0 if there no error. 1 if error occur.
 */
int main()
{
    char line[MAX_LINE_LENGTH];
    int numbers[MAX_LINE_LENGTH] = {0}, result = 0;
    Queue * postfixExpression;
    while (gets(line) != NULL)
    {
        postfixExpression = infixToPostfixConverter(line, numbers);
        result = evaluatePostfixExpression(postfixExpression);
        printf("The value is %d\n", result);
    }
    freeQueue(&postfixExpression);
    return EXIT_SUCCESS;
}