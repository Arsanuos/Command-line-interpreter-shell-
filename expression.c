#include "command_parser.h"
#include "expression.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "StringHandler.h"
#include "variables.h"
#include "expression.h"


bool isExpression(const char* command){

    char* start = command;
    while(isalnum(*start) || *start == '_'){
        start++;
    }
    while(isspace(*start)){
        start++;
    }
    if(*start != '='){
        return false;
    }
    ///no restriction for the rest of the expression.
    return true;
}

char* fetchExpression(const char* expression){
    char* word = NULL;
    int size = 0;
    char* start = expression;
    char c[512];
    memset(c,0,512);

    while(isalpha(*start)){
        start++;
    }
    while(isspace(*start)){
        start++;
    }
    *start = '\0';//add \0 for strdup as copy string for the first to \0
    word = strdup(expression);
    strcat(c , trimwhitespace(word));
    program.exp[0] = strdup(c);
    program.exp[1] = strdup("=");
    start++;//first of the operand
    word = strdup(start);//from start to the \0 at the end
    program.exp[2] = strdup(trimwhitespace(word));
    program.exp[3] = strdup("\0");
    return 0;
}

char* substituteInExpression(char* exp){
    char* start = exp;
    while(*start != '\0'){
        if(*start == '$'){
            ///+1 without $
            char* end = getEndOfVar(exp,start);
            char* var = getVariable(exp,start + 1,end);
            char* val = lookup_variable(var);
            ///replace before $ to the last valid char
            if(val != 0){
                exp = replaceIt(exp,start - 1, end,val);
            }else{
                exp = replaceIt(exp,start - 1 ,end ,"");
            }
            start = exp;
        }
        start++;
    }
    return exp;

}


char* getEndOfVar(char* exp, char* start){
    char* end = start + 1;
    while(isValidChar(*end) && *end != '\0' ){
        end++;
    }
    return end;
}

char* getVariable(char* exp, char* start,char* end){
    /// -1 as end always point to an invalid char look at getEndOfVar().
    char* ret = substring(exp ,start - exp,end - exp - 1);
    return ret;
}

bool isValidChar(char c){

    if(isalnum(c) || c == '_'){
        return true;
    }else{
        return false;
    }
}
