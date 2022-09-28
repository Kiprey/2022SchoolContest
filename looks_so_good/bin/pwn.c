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

void hack() {
    printf("You: It looks so good!\n");
    system("/bin/sh");
}

int main () {
    char buf[0x10];
    my_init();

    printf("You: I, a newbie, even if I dies newbly, I won't call any of your function!\n");
    printf("Kiprey: OK, so, what do you want to say ?");
    read(0, buf, 0x100);
    printf("You: %s", buf);

    return 0;
}