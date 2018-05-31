#include <stdio.h>

int main(){
    char c[50];
    int length = 0;

    length = sprintf(c, "teshan");
    printf("%s len:%d", c, length);

    return 0;
}
