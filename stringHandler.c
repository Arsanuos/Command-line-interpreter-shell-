#include <string.h>

char* substring(char* str,int start , int end){
    char* startOne = str + start;
    char* endOne = str + end;
    char c[end - start + 2];/// new string
    int index = 0;
    while(startOne <= endOne){
        c[index] = *startOne;
        index++;
        startOne++;
    }
    c[index] = 0;
    char* result = strdup(c);
    return result;
}

char* replaceIt(char* str, char* start ,char* end, char* val){

    char* first = substring(str, 0 , start - str);
    char* second = substring(str, end - str , strlen(str) - 1);
    char* res;
    if(first == 0){
        asprintf(&res,"%s%s",val,second);
    }else if(second == 0){
        asprintf(&res, "%s%s",first,val);
    }else{
        asprintf(&res, "%s%s%s",first,val,second);
    }
    return res;
}


char* concatenate(char* str1, char* str2){

    char* result;
    asprintf(&result,"%s%s",str1,str2);
    return result;
}
