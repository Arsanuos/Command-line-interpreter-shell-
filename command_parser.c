#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "command_parser.h"
#include "expression.h"
#include "StringHandler.h"
#include "file_processing.h"
#include <stdio.h>

char* getSpaces(char* nextStart);
char* getNext(char* command ,char* start);
char* getEndOfQuotes(char* pointer);

void parse_command(const char* command ){
    intialize();
	//copy immutable string to another mutable string
	char *result = malloc(strlen(command)+1);
    strcpy(result, command);
    //trim string
    result = trimwhitespace(result);
    if(result[0] == '#'){
        program.isComment = true;
        return;
    }else if(isExpression(result)){
        program.isExpression = true;
        fetchExpression(result);
        return;
    }else if(*(result + strlen(result) - 1) == '&'){
        program.isBackgroud = true;
        result = substring(strdup(result), 0,strlen(result) - 2);
        FILE* log = get_log_file();
        writeToFile(log,concatenate(command," is in background\n"));
    }
    //fetch words
    char** commandWord = split(result," \t");
    if(strcmp(commandWord[0],"cd") == 0){
        program.isCd = true;
    }else if(strcmp(commandWord[0] , "echo") == 0){
        program.isEcho = true;
    }else if(strcmp(commandWord[0] , "history") == 0){
        program.isHandled = true;
        display_history_file();
        return;
    }else if(strcmp(commandWord[0] , "log") == 0){
        program.isHandled = true;
        display_log_file();
        return;
    }else if(strcmp(commandWord[0] , "export") == 0){
        program.name = "export";
        program.isExport = true;
        program.isExpression = true;
        fetchExpression(program.withoutProgramName);
        return;
    }
    char* name = commandWord[0];

    program.name = name;
    program.words = commandWord;
}


char *trimwhitespace(const char *command)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*command)) command++;

  if(*command == 0)  // All spaces?
    return command;

  // Trim trailing space
  end = command + strlen(command) - 1;
  while(end > command && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = '\0';

  return command;
}


char** split(const char* command ,const char* delimiter){

    char* duplicateCommand = strdup(command);
    char** res  = NULL;
    char* word = strtok(command,delimiter);
    program.withoutProgramName = trimwhitespace(substring(duplicateCommand,strlen(word),strlen(duplicateCommand) - 1));
    int n_spaces = 0;
    char* next;


    /* split string and append tokens to 'res' */
    while (word) {
      res = realloc(res, sizeof (char*) * ++n_spaces);
        if (res == NULL)
            exit (-1); /* memory allocation failed */
      res[n_spaces-1] = word;
      next = getNext(command,&word[strlen(word) + 1]);
      if(next != 0 && strcmp(next,"") != 0){
        res = realloc(res, sizeof (char*) * ++n_spaces);
        if (res == NULL)
            exit (-1); /* memory allocation failed */
        res[n_spaces-1] = word;
      }
      do{
        word = strtok (NULL,delimiter);
      }while(word && (word[0] == '"' || word[strlen(word) - 1] == '"') );
    }

    /* realloc one extra element for the last NULL */

    res = realloc (res, sizeof (char*) * (n_spaces+1));
    res[n_spaces] = 0;
    program.sizeOfwords = n_spaces;
    word = 0;
    free(duplicateCommand);
    return res;
}

char* getSpaces(char* start){
    if(start == 0){
        return "";
    }
    int cnt = 0;
    bool sp = true;
    while(true){
        if(isspace(*start)){
            cnt++;
            sp = false;
        }else if(!sp){
            if(!isspace(*start)){
                break;
            }
        }
        start++;
    }
    char* spaces = malloc(cnt + 1);
    memset(spaces,' ',cnt);
    *(spaces+cnt) = 0;
    return spaces;
}

char* getNext(char* command ,char* start){

    if(*start != '"'){
        return "";
    }else{
        start++;
        char* end = getEndOfQuotes(start);
        char* quotes = substring(command,start - command , end - command);
        return quotes;
    }

}

char* getEndOfQuotes(char* pointer){

    while(*pointer != '"'){
        pointer++;
    }
    return pointer - 1;
}


void intialize(){
    program.name = NULL;
    program.words = NULL;
    memset(program.exp,0,512);
    program.str = NULL;
    program.sizeOfwords = 0;
    program.isBackgroud = false;
    program.isCd = false;
    program.isComment = false;
    program.isEcho = false;
    program.isExpression = false;
    program.isHandled = false;
    program.isExport = false;
}

void print_splited(char** res,int size){
        int i = 0;
        for (i = 0; i < (size+1); ++i){
            printf ("res[%d] = %s\n", i, res[i]);
        }
}
