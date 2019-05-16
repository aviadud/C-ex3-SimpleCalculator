/**
 * @file basicMath.h
 * @author Aviad Dudkevich
 * @brief header file for basicMath.c
 */

#ifndef EX3_BASICMATH_H
#define EX3_BASICMATH_H

enum Operators{PLUS = '+', MINUS = '-', MULTIPLY = '*', DIVISION = '/', POWER = '^'};

int precedenceOperator(const char operator1, const char operator2);

int evaluate(const int operand1, const int operand2, const char operator);

#endif //EX3_BASICMATH_H
