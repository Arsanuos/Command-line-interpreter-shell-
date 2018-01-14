HEADERS = command_parser.h commands.h environment.h file_processing.h variables.h StringHandler.h execute.h expression.h
OBJECTS = main.c command_parser.c commands.c environment.c file_processing.c variables.c stringHandler.c execute.c expression.c

default: program

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

program: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f program
