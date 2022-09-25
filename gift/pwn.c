#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void my_init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void error(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    abort();
}

typedef void(*func_t)(void);

int main () {
    char shellcode[0x100];
    my_init();

    printf("You known, "
            "the ability to execute machine code directly, "
            "is the most desirable thing for any hacker.\n");
    printf("Now it's a gift for you.\n");    
    printf("However, I don't want you to get it so easy. :)\n");    
    
    memset(shellcode, '\xf4', sizeof(shellcode));
    size_t size = read(0, shellcode, sizeof(shellcode));
    if(shellcode[size - 1] == '\n')
        size--;
    for(size_t i = 0; i < size; i++) {
        if(!isalnum(shellcode[i])) {
            error("Bad character is detected!");
        }
    }
    func_t sc = (func_t) shellcode;
    sc();

    return 0;
}