#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "variables.h"

char** values;
char** keys;
int keySize = 0;
int valuesSize = 0;
const char* ret;

const char* lookup_variable( const char* key )
{
	int i = 0;
	for(i = 0;i < keySize; i++){
        if(strcmp(keys[i],key) == 0){
            return values[i];
        }
	}
	if(getenv(key) == 0)
    {
        return 0;
    }
    ret = strdup(getenv(key));
    return strdup(ret);
}

int getIndex(const char* key){

    int i = 0;
	for(i = 0;i < keySize; i++){
        if(strcmp(keys[i],key) == 0){
            return i;
        }
	}
	return getenv(key) == 0 ? -1 : -50;
}

void set_variable( const char* key , const char* value )
{
    if(lookup_variable(key) == 0){///not exists anywhere
        create(key ,value);
    }else{
         ///just modify the current val in our array.
        int index = getIndex(key);
        if(index == -50){///exists in env but not in our array.
            create(key , value);
        }else if(index >= 0 && index < keySize){
            values[index] = value;
            keys[index] = key;
        }
    }
}

void create(char* key , char* value){

    if(key) {
      keys = realloc(keys, sizeof (char*) * ++keySize);

        if (keys == NULL)
            exit (-1); /* memory allocation failed */
      keys[keySize-1] = key;
    }

    if(value) {
      values = realloc(values, sizeof (char*) * ++valuesSize);

        if (values == NULL)
            exit (-1); /* memory allocation failed */
      values[valuesSize-1] = value;
    }

}

void print_all_variables()
{
    int i = 0;
    for (i = 0; i < keySize; ++i){
        printf ("values[%s] = %s\n", keys[i], values[i]);
    }
}
