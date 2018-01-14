#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "command_parser.h"
#include "variables.h"
#include "StringHandler.h"
#include "file_processing.h"
#include "expression.h"
#include <stdlib.h>


void cd( const char* path )
{
   char cwd[500];
   if(path == 0){
        chdir(lookup_variable("HOME"));
    }else if (path[0] == '~'){
        chdir(lookup_variable("HOME"));
        const char* g = strdup(substring(path,2,strlen(path)));
        chdir(g);
    }else if(path[0] != '/'){// true for the dir in current working directory
        chdir(path);
    }else{//true for dir w.r.t. root
        chdir(path);
    }
    FILE* log = get_log_file();
    getcwd(cwd, sizeof(cwd));
    writeToFile(log,concatenate(concatenate("directory changed to ",cwd),"\n"));
    return;
}


void echo( const char* message )
{
    char* val = removeQuotes(message);
    val = substituteInExpression(val);
    printf(val);
    printf("\n");
}

void exportVar(char* express[]){
    expression(express);
}

void expression(char* express[]){
   set_variable(express[0], trimwhitespace(removeQuotes(express[2])));
}

char* removeQuotes(char* str){
    ///+1 for \0
    char* start = str;
    char* c = malloc(strlen(str) + 1);
    int i = 0;
    while(*start != '\0'){
        if(*start != '"'){
            c[i] = *start;
            i++;
        }
        start++;
    }
    c[i] = 0;
    return c;
}
