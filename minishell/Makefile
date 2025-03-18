CC = cc

LIBS = -lreadline
SRCS = minishell.c src/make_tree.c libft/libft.a src/make_algo_stacks.c src/syntax_error.c src/make_list.c src/tokenizer.c
OBJS = $(SRCS:.c=.o)
TARGET = minishell

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re