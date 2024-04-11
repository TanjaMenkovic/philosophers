SRC_FILES =  errors.c main.c simulation.c utils_philo.c init.c	utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	${CC} ${CFLAGS} ${OBJ_FILES}  -o ${NAME} 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean
