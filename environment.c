#include "environment.h"
#include <string.h>
#include <ctype.h>
#include "command_parser.h"
#include <stdio.h>
#include "file_processing.h"
#include <unistd.h>

void setup_environment()
{

    //open files
    open_history_file();
    open_log_file();

}


char* getCurrentDirectory(){

    memset(cwd,0,512);
    getcwd(cwd,sizeof(cwd));
    return &(cwd[0]);
}
