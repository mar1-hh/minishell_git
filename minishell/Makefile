CC = cc

LIBS = -lreadline
SRCS = minishell.c src/make_tree.c libft/libft.a src/make_algo_stacks.c src/syntax_error.c src/make_list.c src/tokenizer.c
OBJS = $(SRCS:.c=.o)
TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJS) libft/libft.a
	$(CC) -o $(TARGET) $(OBJS) $(LIBS) -Llibft -lft

libft/libft.a:
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(TARGET)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re