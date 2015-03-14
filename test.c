#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("usage: %s <link>\n", argv[0]);
        return 0;
    }

    char buf[512];
    int count = readlink(argv[1], buf, sizeof(buf));
    if (count >= 0) {
        buf[count] = '\0';
        printf("%s -> %s\n", argv[1], buf);
    }

    return 0;

}