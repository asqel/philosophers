NAME = philo

SRCS = $(wildcard *.c)
OBJ = ${SRCS:.c=.o}

CC = cc
LD = cc
CFLAGS = -g #-Wall -Wextra -Werror
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