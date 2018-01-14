#include "file_processing.h"
#include <stdio.h>

char* historyFileName = "history.txt";
char* logFileName = "log.txt";
char* batchFilePath = "/media/arsanuos/42096389-e9a4-4305-beb5-98c32730190b/OS/Session_1_material/assignment1/shell/Shell/testCase2";
FILE* historyFile;
FILE* logFile;
FILE* batchFile;

typedef enum{ false = 0 , true = 1 } bool ;

/*
	history file section
*/
void open_history_file()
{
	//open for reading and appending
	historyFile = fopen("history.txt","a+");
}

FILE* get_history_file()
{
	//return file
	return historyFile;
}

void close_history_file()
{
	//close file
	fclose(historyFile);
}


/*
	log file section
*/
void open_log_file()
{
	//open for reading and appending
	logFile = fopen("log.txt","a+");
}

FILE* get_log_file()
{
	//return log file
	return logFile;
}

void close_log_file()
{
	//close log file
	fclose(logFile);
}


/*
	CommandsBatch file section
*/
void open_commands_batch_file(char* batchFilePathArg)
{
    batchFilePath = batchFilePathArg;
    if(strcmp(batchFilePath, "") != 0){
        //open batch file
        batchFile = fopen(batchFilePath,"r");
    }else{
        /// can't open file
    }
}

FILE* get_commands_batch_file()
{
	return batchFile != 0 ? batchFile : 0;
}

void close_commands_batch_file()
{
    if(batchFile != 0){
        fclose(batchFile);
    }
}



void writeToFile(FILE* file , const char* message){
    fputs(message,file);
    fflush(file);
}


void display_history_file(){
    seekToBegining(historyFile);
    char str[512];
    while(true){
        memset(str,0,512);
        if(fgets(str, 512 ,historyFile) == NULL){
            break;
        }
        printf("%s",str);
    }
    seekToEnd(historyFile);
}

void display_log_file(){
    seekToBegining(logFile);
    char str[512];
    while(true){
        memset(str,0,512);
        if(fgets(str, 512 ,logFile) == NULL){
            break;
        }
        printf("%s",str);
    }
    seekToEnd(logFile);
}

void seekToEnd(FILE* file){
    fseek(file,0,SEEK_END);
}

void seekToBegining(FILE* file){
    fseek(file,0,SEEK_SET);
}
