#include "../pipex.h"

static char	*find_path(char **env)
{
	int		i;
	char	*path_env;

	i = 0;
	path_env = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	return (path_env);
}

static char	*check_path(char **cmd_args, char **paths)
{
	int		i;
	char	*full_path;

	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd_args[0]);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (NULL);
}

char	**get_path(char *cmd, char **env)
{
	char	**cmd_args;
	char	**paths;
	char	*path_env;
	char	*full_path;

	full_path = NULL;
	path_env = find_path(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
		return (ft_free_split(paths), NULL);
	full_path = check_path(cmd_args, paths);
	ft_free_split(paths);
	if (!full_path)
		return (ft_free_split(cmd_args), NULL);
	free(cmd_args[0]);
	cmd_args[0] = full_path;
	return (cmd_args);
}
