char headers[] = "#include <stdio.h>\n#include <sys/types.h>\n#include <sys/stat.h>\n#include <fcntl.h>\n#include <string.h>\n#include <unistd.h>\n#include <time.h>\n#include <stdlib.h>\n";
char str[] = "void write_string (int fd, char * astr){int i;for (i = 0; i < strlen(astr); i++){if (astr[i] == '\\n'){write(fd, \"\\\\n\", 2);}else if (astr[i] == '%'){if (astr[i+1] == 'd'){write(fd, \"\\\\\", 1);write(fd, &astr[i], 1);}else{write(fd, &astr[i], 1);}}else if (astr[i] == '\"' || astr[i] == '\\\\'){write(fd, \"\\\\\", 1);write(fd, &astr[i], 1);}else{write(fd, &astr[i], 1);}}} int main (){srand(time(NULL));int r = rand() % 50;char c_file[6];char file[6];char print[40];memset(c_file, 0x0, 6);memset(file, 0x0, 6);memset(print, 0x0, 40);sprintf(c_file, \"v\%d.c\", r);sprintf(file, \"v\%d\", r);sprintf(print, \"printf(\\\"rand num: \%d\\\\n\\\");\", r);int fd = open(c_file, O_WRONLY | O_CREAT, 0744);write(fd, \" char str[] = \\\"\", strlen(\" char str[] = \\\"\"));write_string(fd, str);write(fd, \"\\\";\\n\", strlen(\"\\\";\\n\"));write(fd, \" char headers[] = \\\"\", strlen(\" char headers[] = \\\"\"));write_string(fd, headers);write(fd, \"\\\";\\n\", strlen(\"\\\";\\n\"));write(fd, \" char str2[] = \\\"}}\\\";\\n\", strlen(\" char str2[] = \\\"}}\\\";\\n\"));write(fd, headers, strlen(headers));write(fd, str, strlen(str));write(fd, print, strlen(print));write(fd, str2, strlen(str2));close(fd);pid_t pid = fork();char * args[] = {\"gcc\\0\", \"-o\\0\", file, c_file, NULL};if (pid == 0){execvp(\"gcc\\0\", args);}else {";
char str2[] = "}}";

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void write_string (int fd, char * astr)
{
    int i;
    for (i = 0; i < strlen(astr); i++)
    {
        if (astr[i] == '\n')
        {
            write(fd, "\\n", 2);
        }
        else if (astr[i] == '%')
        {
            if (astr[i+1] == 'd')
            {
                write(fd, "\\", 1);
                write(fd, &astr[i], 1);
            }
            else
            {
                write(fd, &astr[i], 1);
            }
        }
        else if (astr[i] == '"' || astr[i] == '\\')
        {
            write(fd, "\\", 1);
            write(fd, &astr[i], 1);
        }
        else
        {
            write(fd, &astr[i], 1);
        }
    }
}

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
    sprintf(print, "printf(\"rand num: %d\\n\");", r);

    int fd = open(c_file, O_WRONLY | O_CREAT, 0744);
    write(fd, " char str[] = \"", strlen(" char str[] = \""));
    write_string(fd, str);
    write(fd, "\";\n", strlen("\";\n"));

    write(fd, " char headers[] = \"", strlen(" char headers[] = \""));
    write_string(fd, headers);
    write(fd, "\";\n", strlen("\";\n"));
    
    write(fd, " char str2[] = \"}}\";\n", strlen(" char str2[] = \"}}\";\n"));


    write(fd, headers, strlen(headers));
    write(fd, str, strlen(str));
    write(fd, print, strlen(print));
    write(fd, str2, strlen(str2));

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
