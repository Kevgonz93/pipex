#include "data.h"
#include "aux/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// UTILS

void	init_struct(int argc, char **argv, t_data *pipex);
int		*create_pipes(int size);
char	*ft_strjoin_free(char *s1, const char *s2);
void	ft_free_split(char **split);
int		open_file(char *file, char *side);

//PATHS

char	**get_path(char *cmd, char **env);

//PIPEX

void	exec_cmd(t_data *pipex, int cmd_index);
void	finish_program(t_data *pipex);
