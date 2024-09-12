SRC =	src/error.c \
		src/init.c \
		src/monitor.c \
		src/philo.c \
		src/safe_atoi.c \
		src/simulation.c \
		src/time.c \
		src/tools.c

NAME = philo

CFLAGS = -Werror -Wall -Wextra #-g -fsanitize=thread

$(NAME) : $(SRC)
	cc $(CFLAGS) $(SRC) -o $(NAME)

all : $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:
	all clean fclean re