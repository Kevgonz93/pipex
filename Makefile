NAME = pipex

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard *.c)
SRCS_LIBFT = $(wildcard aux/*.c)
SRCS_SRC = $(wildcard src/*.c)
SRCS_ALL = $(SRCS) $(SRCS_LIBFT) $(SRCS_SRC)

OBJS = $(SRCS_ALL:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
