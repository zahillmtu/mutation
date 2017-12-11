char str[] = "#include <stdio.h>\n int main (){";
char str2[] = "printf(\"testing \");";
char str3[] = "}";
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main ()
{
    srand(time(NULL));
    int r = rand() % 50;
    char c_file[6];
    char file[6];
    char print[40];
    memset(c_file, 0x0, 6);
    memset(file, 0x0, 6);
    memset(print, 0x0, 40);
    sprintf(c_file, "v%d.c", r);
    sprintf(file, "v%d", r);
    sprintf(print, "printf(\"rand num: %d\");", r);

    int fd = open(c_file, O_WRONLY | O_CREAT, 0744);
    write(fd, str, strlen(str));
    write(fd, str2, strlen(str2));
    write(fd, print, strlen(print));
    write(fd, str3, strlen(str3));

    close(fd);
    pid_t pid = fork();
    char * args[] = {"gcc\0", "-o\0", file, c_file, NULL};
    if (pid == 0)
    {
        execvp("gcc\0", args);
    }
    else 
    {
        printf("testing version: %d\n", r);
    }
}
