#ifndef COMMAND_PARSER_H   /* Include guard */
#define COMMAND_PARSER_H

/*
	- This function should be responsible for importing all details of the command
	- Should specify the type of the command "comment, cd, echo, expression - X=5 -, else"
	- Should specify the arguments of the command
	- Should specify if the command is background or foreground
	- Should consider all parsing special cases, example: many spaces in  "ls     -a"

	- You're left free to decide how to return your imported details of this command

	- Best practice is to use helper function for each collection of logical instructions,
	  example: function for splitting the command by space into array of strings, ..etc
*/

typedef enum{ false = 0 , true = 1 } bool ;

struct Program{
    char* str;
    char* name;
    char** words;
    bool isComment;
    bool isCd;
    bool isEcho;
    bool isBackgroud;
    bool isExpression;
    int sizeOfwords;
    char* exp[4];
    bool isHandled;
    char* withoutProgramName;
    bool isExport;
};

struct Program program;

void parse_command( const char* command );

char *trimwhitespace(const char *command);

char** split(const char* commmand ,const char* delimiter);

void intialize();

char* getSpaces(char* nextStart);

char* getNext(char* command ,char* start);

char* getEndOfQuotes(char* pointer);



#endif // COMMAND_PARSER_H
