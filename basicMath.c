/**
 * @file basicMath.c
 * @author Aviad Dudkevich
 *
 * @brief function of basic math.
 */

#include <stdio.h>
#include "basicMath.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

const char OPERATOR_ERROR_MSG[] = "Error: unsupported operator.\n";
const char DIVISION_BY_ZERO_ERROR_MSG[] = "Error: Division by 0.\n";

/**
 * @brief Determine if operator1 precedence operator2.
 * @param operator1 - char representing operator1.
 * @param operator2 - char representing operator2.
 * @return false or true.
 */
int precedenceOperator(const char operator1, const char operator2)
{
    switch (operator1)
    {
        case PLUS:
        case MINUS:
            if (operator2 == POWER || operator2 == DIVISION || operator2 == MULTIPLY)
            {
                return false;
            }
            else
            {
                return true;
            }
        case MULTIPLY:
        case DIVISION:
            if (operator2 == POWER)
            {
                return false;
            }
            else
            {
                return true;
            }
        case POWER:
            return true;
        default:
            fprintf(stderr, OPERATOR_ERROR_MSG);
            return false;
    }
}

/**
 * @brief Evaluate arithmetic expression in integer.
 * @param operand1 - char representing operand1.
 * @param operand2 - char representing operand2.
 * @param operator - char representing the operator.
 * @return integer of the Evaluation.
 */
int evaluate(const int operand1, const int operand2, const char operator)
{
    switch (operator)
    {
        case PLUS:
            return operand1 + operand2;
        case MINUS:
            return operand1 - operand2;
        case MULTIPLY:
            return operand1 * operand2;
        case DIVISION:
            if (operand2 == 0)
            {
                fprintf(stderr, DIVISION_BY_ZERO_ERROR_MSG);
                exit(EXIT_FAILURE);
            }
            return operand1 / operand2;
        case POWER:
            return (int) pow((double) operand1, (double) operand2);
        default:
            fprintf(stderr, OPERATOR_ERROR_MSG);
            return false;
    }
}
