#include "pipex.h"

void	exec_cmd(char **cmd, int *pipes, int total_pipes, int cmd_index, int fd_in, int fd_out)
{
	int	prev_pipe;
	int	next_pipe;

	prev_pipe = (cmd_index - 1) * 2;
	next_pipe = cmd_index * 2;

	if (cmd_index == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(pipes[next_pipe + 1], STDOUT_FILENO);
	}
	else if (cmd_index == total_pipes)
	{
		dup2(pipes[prev_pipe], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
	}
	else
	{
		dup2(pipes[prev_pipe], STDIN_FILENO);
		dup2(pipes[next_pipe + 1], STDOUT_FILENO);
	}

	for (int i = 0; i < total_pipes * 2; i++)
		close(pipes[i]);

	close(fd_in);
	close(fd_out);
	execve(cmd[0], cmd, NULL);
	perror("execve error");
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	int		total_pipes;
	int		*pipes;
	int		fd_in;
	int		fd_out;
	int		i;
	char	**cmd;

	if (argc < 5)
		return (perror("Error: Invalid number of arguments"), 1);
	// i = 0;
	// while (env[i])
	// {
	// 	printf("env[%d] = %s\n", i, env[i]);
	// 	i++;
	// }
	total_pipes = argc - 4;
	pipes = malloc(sizeof(int) * total_pipes * 2);
	if (!pipes)
		return (perror("malloc error"), 1);
	i = 0;
	for (i = 0; i < total_pipes; i++)
		if (pipe(pipes + (i * 2)) == -1)
			return (perror("pipe error"), free(pipes), 1);

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		return (perror("open error"), free(pipes), 1);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (perror("open error"), close(fd_in), free(pipes), 1);

	i = 0;
	while (i < total_pipes + 1)
	{
		cmd = get_path(argv[i + 2], env);
		if (!cmd)
			return (perror("Error: Command not found"), free(pipes), 1);

		if (fork() == 0)
			exec_cmd(cmd, pipes, total_pipes, i, fd_in, fd_out);

		ft_free_split(cmd);
		i++;
	}
	for (i = 0; i < total_pipes * 2; i++)
		close(pipes[i]);
	free(pipes);
	while (wait(NULL) > 0)
		;

	close(fd_in);
	close(fd_out);
	return (0);
}
