OBJS = \
		pipex_main.o \

all: pipex

pipex: $(OBJS)
	cc $^ -Werror -Wextra -Wall libft/ft_base/libft.a libft/ft_printf/libftprintf.a -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f pipex

re: fclean all