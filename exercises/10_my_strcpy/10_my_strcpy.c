#include <stdio.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
	int p = 0 ;
    char c = source[p];

    do{
        c = source[p];
        destination[p] = c;
        p++;
    }while(c!='\0');

    


    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}