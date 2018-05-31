#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    char s[] = "tesha/"
"fweg/"
"affew";
    printf("%s\n",  s);
    char *tok = strtok(s, "/");
    while(tok != NULL){
        printf("%s\n", tok);
        tok = strtok(NULL, "/");
    }
    return 0;
}
