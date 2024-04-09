#include <stdio.h>
#include <stdlib.h>
void    check(char **line)
{
    printf("%s\n", *line);
    *line += 1;
}

int main()
{
    char    *line;
    
    line = malloc(sizeof(char) * 12+1);

    line =  "je suis Simo";

    printf("%s\n", line);
    while (*line)
    {
        check(&line);
    }
}