#ifndef COMMANDS_H_   /* Include guard */
#define COMMANDS_H_

/*
	- This function should be responsible for implementing the "cd" shell command
*/
void cd( const char* path );

/*
	- This function should be responsible for implementing the "echo" shell command
	- Typically should lookup any variable included in the message
*/
void echo( const char* message );


char* removeQuotes(char* str);

void expression(char* express[]);

#endif // COMMANDS_H_
