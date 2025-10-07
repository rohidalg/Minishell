#include "../minishell.h"

void    built_cd(char **cmd)
{
    if (cmd[1] == NULL)
        chdir(getenv(cd));
    else if(cmd[1] != 0)
        perror("cd");
}

// Probando, hay que verificar todas las opciones, directorio anterior con .. y con -, directorio actual.