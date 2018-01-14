#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "execute.h"
#include "environment.h"
#include "command_parser.h"
#include "variables.h"
#include "file_processing.h"
#include <stdlib.h>

void execute(){

    signal(SIGCHLD , afterTermination);
    pid_t pid;
    pid = getpid();
    pid = fork();
    getPathes();
    int i = 0;
    char* res;
    if(!pid){
        /// try all pathes.
        while(pathes[i] != 0){
            asprintf(&res,"%s/%s",pathes[i],program.name);
            execv(res,program.words);
            i++;
        }
        ///user enter the right path.
        asprintf(&res,"%s",program.name);
        execv(res,program.words);
        ///user enter a path which complete the current directory
        getCurrentDirectory();
        asprintf(&res ,"%s/%s",cwd,program.name);
        printf("Unknown command\n");
        exit(-1);
    }
    if(!program.isBackgroud){
        int status;
        do{
            waitpid(pid, &status, WUNTRACED);
        }while( !WIFEXITED(status) && !WIFSIGNALED(status) );
    }
}

void getPathes(){
    pathes = split(lookup_variable("PATH"),":");
}


void afterTermination(){
    writeToFile(get_log_file(),"Child process was terminated.\n");
}
