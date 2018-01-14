#ifndef EXPRESSION_H   /* Include guard */
#define EXPRESSION_H

char* substituteInExpression(char* exp);

char* getEndOfVar(char* exp, char* start);

char* getVariable(char* exp, char* start,char* end);

bool isValidChar(char c);

bool isExpression(const char* command);

char* fetchExpression(const char* expression);

#endif
