#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include "environment.h"
#include "StringHandler.h"
#include "command_parser.h"
#include "expression.h"
#include "variables.h"
#include "commands.h"
#include "execute.h"
#include "file_processing.h"



void start();
void start_shell(bool read_from_file);
void shell_loop(bool input_from_file);
char** subsBeforeExecution(char** args);
void handle();

int main(int argc, char *argv[])
{
    bool x[54];
    x[0] = 1;
    setup_environment();
    signal(SIGSEGV,handle);
    // any other early configuration should be here
    if( argc > 1 ){
        open_commands_batch_file(argv[1]);
        start(true);
    }
    else{
        start(false);
    }

    return 0;
}

void start(bool read_from_file)
{
	cd(getenv("HOME")); // let shell starts from home

	if(read_from_file){
		// file processing functions should be called from here

		shell_loop(true);
	}
	else{
		shell_loop(false);
	}
}

void shell_loop(bool input_from_file)
{
	bool from_file = input_from_file;
    size_t buffer_size = 512;
    char *str = malloc(buffer_size * sizeof(char));
    FILE* batch = get_commands_batch_file();
    FILE* log = get_log_file();
    FILE* history = get_history_file();
	while(true){
		if(from_file){
            //usleep(900000);
			if(batch == NULL){
                return;
            }
            else{
                if(getline(&str, &buffer_size, batch) == -1){
                    from_file = false;
                    continue;
                }
                printf("Shell %s :>",getCurrentDirectory());
                printf("%s\n",str);
                const char* message;
                asprintf(&message , "%s%s%s","Instruction " , trimwhitespace(str) , " fetched\n");
                writeToFile(log,message);
                writeToFile(history,concatenate(trimwhitespace(str),"\n"));
                free(message);
                if(strcasecmp(str,"exit\n") == 0 || strcasecmp(str ,"exit") == 0){
                    from_file = false;
                    continue;
                }
                run(str);
                fflush(stdout);
                continue;
            }
        }
        if(interactive() == -1){
            return;
        }
	}
   // free(str);
}

void run(char str[]){
    if(str[0] == '\n' || str[1] == '\n'){
        return;
    }
    str = substituteInExpression(str);
    parse_command(str);
    if(!program.isComment){
        if(program.isCd){
            cd(program.words[1]);
        }else if(program.isEcho){
            echo(program.withoutProgramName);
        }else if(program.isExpression){
            expression(program.exp);
            //print_all_variables();
        }else if (program.isExport) {
            exportVar(program.exp);
        }else if(!program.isHandled){
            execute();
        }
    }
    FILE* log = get_log_file();
    const char* message;
    asprintf(&message , "%s%s%s","Instruction " , trimwhitespace(str) , " executed.\n");
    writeToFile(log,message);
}

int interactive(){

        FILE* log = get_log_file();
        FILE* history = get_history_file();
        char str[512];
        printf("Shell %s :>",getCurrentDirectory());
        if (fgets(str, 512, stdin) == NULL || strcasecmp(str,"exit\n") == 0) {
           return -1;
        }
        const char* message;
        asprintf(&message , "%s%s%s","Instruction " , trimwhitespace(str) , " fetched\n");
        writeToFile(log,message);
        writeToFile(history,concatenate(trimwhitespace(str),"\n"));
        if(strcmp(str, "\n") != 0){
            run(str);
        }
    return 0;
}

char** subsBeforeExecution(char** args){

    int i = 0;
    while(args[i] != '\0'){
        args[i] = substituteInExpression(args[i]);
        i++;
    }
    return args;
}

void handle(){
    printf("out\n");
    perror("Error is ");
    exit(-1);
}
