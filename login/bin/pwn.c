#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void my_init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void error(const char* msg) {
    fprintf(stderr, "%s\n", msg);
    abort();
}

void gen_passwd(char* buf, size_t size) {
    int fd;
    sleep(1);
    if((fd = open("/dev/random", O_RDONLY)) < 0)
        error("Cannot open /dev/random");
    for (size_t i = 0; i < size; i++) {
        unsigned char ch;
        if(read(fd, &ch, 1) <= 0)        
            error("Cannot read data from /dev/random");
        buf[i] = (ch % 26) + 'a';
    }
    buf[size - 1] = '\0';
}

int main () {
    char secret_passwd[0x10 + 1];
    char input_passwd[0x30];

    my_init();
    printf("Try to login the shell!\n");
    printf("(Kiprey: You will never guess my password. HAHA)\n");

    printf("Generating %ld bits password...", sizeof(secret_passwd) - 1);
    gen_passwd(secret_passwd, sizeof(secret_passwd));
    printf("Done!\n");

    printf("Please input the password: ");
    scanf("%s", input_passwd);

    if(!strncmp(input_passwd, secret_passwd, strlen(secret_passwd))) {
        printf("Loging success! Welcome Kiprey...\n");
        system("/bin/sh");
    }
    else {
        printf("Password wrong, quitting...\n");
    }

    return 0;
}