#ifndef DATA_H
# define DATA_H

typedef struct s_data
{
	char	**cmd;
	char	**env;
	char	*file_in;
	char	*file_out;
	int		fd_in;
	int		fd_out;
	int		*pipes;
	int		total_pipes;
}	t_data;

#endif