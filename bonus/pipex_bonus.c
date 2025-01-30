#include "pipex_bonus.h"

// $> ./pipex here\_doc LIMITADOR comando comando1 archivo

// comando << LIMITADOR | comando1 >> archivo

int	main(int argc, char **argv)
{
	(void)argc;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		printf("here_doc detected\n");

	}
	return (0);
}
