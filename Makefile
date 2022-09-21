NAME = philo
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g
RM = rm -rf

SRC = main.c philos.c cycle.c death_check.c tools.c
OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:	
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
