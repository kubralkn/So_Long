#include "so_long.h"

void error_msg(char *str)
{
    ft_printf("%s", str);
    exit(1);
}

void check_file(char *str)
{
    int len;

    len = ft_strlen(str);
    if (!(str[len - 1] == 'r' && str[len - 2] == 'e' 
            && str[len - 3] == 'b' && str[len - 4] == '.'))
        error_msg("wrong filename");

    int fd;
    
    fd = open(str , O_RDONLY);
    if (fd < 0)
        error_msg("map wrong file");
    close(fd);
}
