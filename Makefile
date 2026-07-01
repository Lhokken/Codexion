NAME = lib_codex.a

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRCS = codex.c round_list.c inizialize_codex.c

OBJS = $(SRCS:.c=.o)

TEST_SRC = codex.c

TEST_NAME = test

all: $(NAME) cc

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OBJS) $(NAME) $(TEST_NAME)

re: fclean all

cc: $(NAME) $(TEST_SRC)
	$(CC) $(CFLAGS) $(SRCS) -L. -l_codex -o $(TEST_NAME)

run:
	./$(TEST_NAME) 10 200 200 500 600 100 250 fifo

val:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(TEST_NAME) 10 200 200 500 600 100 250 fifo
.PHONY: all clean fclean re cc run val
