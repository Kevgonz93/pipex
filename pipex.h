#include "aux/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// UTILS

char	*ft_strjoin_free(char *s1, const char *s2);
void	ft_free_split(char **split);
int		get_size(int *pipes);
int		open_file(char *file, char *side);

//PATHS

char	**get_path(char *cmd, char **env);

//PIPEX

int		*make_pipes(int total_pipes);
void	make_conections(int cmd_index, int *pipes, int fd_in, int fd_out);

