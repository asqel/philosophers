NAME = philo

SRCS = atoi.c  forks.c  gets.c  init.c  main.c  mother.c  philo.c  print.c  time.c
OBJ = ${SRCS:.c=.o}

CC = cc
LD = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lpthread

all: $(NAME)

$(NAME): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

debug: $(NAME)
	valgrind --tool=helgrind ./$(NAME)

.PHONY: all clean fclean re