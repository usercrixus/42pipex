OBJS = \
		pipex_main.o \
		pipex_get_command.o \
		pipex_pipe_command.o \

all: submodule libft.a pipex

pipex: $(OBJS)
	cc $^ -Werror -Wextra -Wall libft/ft_base/libft.a libft/ft_printf/libftprintf.a -o $@

submodule:
	git submodule update --init --recursive

libft.a:
	make -C ./libft all

clean:
	rm -f $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -f pipex
	make -C ./libft fclean

re: clean fclean all

.PHONY: clean fclean re libft.a 