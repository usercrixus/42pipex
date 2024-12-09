OBJS = \
		pipex_main.o \
		pipex_get_command.o \
		pipex_pipe_command.o \
		pipex_set_input_output.o \

all: submodule libft.a pipex

pipex: $(OBJS)
	cc $^ -Werror -Wextra -Wall libft/ft_base/libft.a libft/ft_printf/libftprintf.a libft/ft_gnl/libftgnl.a -o $@

submodule:
	git submodule update --init --recursive

libft.a:
	make -C ./libft all

test1:
	./pipex input.txt cat wc wc ouput.txt

test2:
	./pipex input.txt cat wc ouput.txt

clean:
	rm -f $(OBJS)
	make -C ./libft clean

fclean: clean
	rm -f pipex
	make -C ./libft fclean

re: clean fclean all

.PHONY: clean fclean re libft.a 