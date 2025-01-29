#include    "pipex.h"

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

int	get_size(int *pipes)
{
	int		i;

	i = 0;
	while (pipes[i])
		i++;
	return (i);
}

int	open_file(char *file, char *side)
{
	int	fd;

	fd = -1;
	if (ft_strncmp(side, "in", 2) == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			exit(1);
	}
	else if (ft_strncmp(side, "out", 3) == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
	}
	return (fd);
}
