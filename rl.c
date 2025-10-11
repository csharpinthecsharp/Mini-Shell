#include "include/minishell.h"

char *rl(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static int buffer_pos = 0;
    static int buffer_size = 0;
    char *line;
    int line_len = 0;
    int i;
    
    static char temp_line[100000];
    if (fd < 0)
        return NULL;
    
    while (1)
    {
        if (buffer_pos >= buffer_size)
        {
            buffer_size = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            
            if (buffer_size <= 0)
            {
                if (line_len == 0)
                    return NULL;
                break;
            }
        }
        
        while (buffer_pos < buffer_size)
        {
            temp_line[line_len] = buffer[buffer_pos];
            buffer_pos++;
            line_len++;
            
            if (temp_line[line_len - 1] == '\n')
            {
                temp_line[line_len] = '\0';
                
                line = malloc(line_len + 1);
                if (!line)
                    return NULL;
                
                i = 0;
                while (i < line_len)
                {
                    line[i] = temp_line[i];
                    i++;
                }
                line[i] = '\0';
                
                return line;
            }
        }
    }
    
    if (line_len > 0)
    {
        temp_line[line_len] = '\0';
        
        line = malloc(line_len + 1);
        if (!line)
            return NULL;
        
        i = 0;
        while (i < line_len)
        {
            line[i] = temp_line[i];
            i++;
        }
        line[i] = '\0';
        
        return line;
    }
    
    return NULL;
}