#include "pipex.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	if (!result)
		return (NULL);
	free(s1);
	return (result);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	init_struct(int argc, char **argv, t_data *pipex)
{
	pipex->cmd = NULL;
	pipex->env = NULL;
	pipex->file_in = argv[1];
	pipex->file_out = argv[argc - 1];
	pipex->fd_in = open_file(argv[1], "in");
	pipex->fd_out = open_file(argv[argc - 1], "out");
	pipex->pipes = create_pipes(argc - 4);
	pipex->total_pipes = argc - 4;
}

int	*create_pipes(int size)
{
	int	*pipes;
	int	i;

	pipes = malloc(sizeof(int) * size * 2);
	if (!pipes)
		return (perror("malloc error"), NULL);
	i = 0;
	while (i < size)
	{
		if (pipe(pipes + (i * 2)) == -1)
			return (perror("pipe error"), free(pipes), NULL);
		i++;
	}
	return (pipes);
}

int	open_file(char *file, char *side)
{
	int	fd;

	printf("opening file %s\n", file);
	fd = -1;
	if (ft_strncmp(side, "in", 2) == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			perror("open error");
			exit(1);
		}
	}
	else
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open error");
			exit(1);
		}
	}
	return (fd);
}
