#include "pipex.h"

static void	first_dup(t_data *pipex)
{
	dup2(pipex->fd_in, STDIN_FILENO);
	dup2(pipex->pipes[1], STDOUT_FILENO);
}

static void	last_dup(t_data *pipex)
{
	dup2(pipex->pipes[pipex->total_pipes * 2 - 2], STDIN_FILENO);
	dup2(pipex->fd_out, STDOUT_FILENO);
}

void	exec_cmd(t_data *pipex, int cmd_index)
{
	int	prev_pipe;
	int	next_pipe;
	int	i;

	printf("executing command %s\n", pipex->cmd[0]);
	prev_pipe = (cmd_index - 1) * 2;
	next_pipe = cmd_index * 2;
	if (cmd_index == 0)
		first_dup(pipex);
	else if (cmd_index == pipex->total_pipes)
		last_dup(pipex);
	else
	{
		dup2(pipex->pipes[prev_pipe], STDIN_FILENO);
		dup2(pipex->pipes[next_pipe + 1], STDOUT_FILENO);
	}
	i = 0;
	while (i < pipex->total_pipes * 2)
		close(pipex->pipes[i++]);
	execve(pipex->cmd[0], pipex->cmd, NULL);
	perror("execve error");
	exit(1);
}

void	finish_program(t_data *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->total_pipes * 2)
	{
		close(pipex->pipes[i]);
		i++;
	}
	if (pipex->pipes)
		free(pipex->pipes);
	while (wait(NULL) > 0)
		;
	if (pipex->fd_in)
		close(pipex->fd_in);
	if (pipex->fd_out)
		close(pipex->fd_out);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_data	*pipex;

	if (argc < 5)
		return (perror("Error: Invalid number of arguments"), 1);
	pipex = malloc(sizeof(t_data));
	printf("initiating struct\n");
	init_struct(argc, argv, pipex);
	i = 0;
	while (i < argc - 3)
	{
		pipex->cmd = get_path(argv[i + 2], env);
		if (!pipex->cmd)
			return (perror("Error: Command not found"), free(pipex->pipes), 1);
		if (fork() == 0)
			exec_cmd(pipex, i);
		ft_free_split(pipex->cmd);
		i++;
	}
	printf("finishing program\n");
	finish_program(pipex);
	return (0);
}
