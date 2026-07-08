NAME = lib_codex.a

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -pthread

SRCS = codex.c round_list.c inizialize_codex.c dongle_inizialize.c work_steps.c codex_priority.c codex_error.c

OBJS = $(SRCS:.c=.o)

TEST_SRC = codex.c

TEST_NAME = codexion

TEST_DATA = 23 90 80 50 60 20 90 fifo

VALG = valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes -s

HELG = valgrind -s --tool=helgrind

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME) cc run

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME) $(TEST_NAME)

re: fclean all clean

cc: $(NAME) $(TEST_SRC)
	$(CC) $(CFLAGS) $(SRCS) -L. -l_codex -o $(TEST_NAME)

run:
	./$(TEST_NAME) $(TEST_DATA)

val:
	$(VALG) ./$(TEST_NAME) $(TEST_DATA)

hel:
	$(HELG) ./$(TEST_NAME) $(TEST_DATA)

.PHONY: all clean fclean re cc run val hel
