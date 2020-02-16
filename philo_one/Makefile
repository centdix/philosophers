DIR_O = objs

SRCS = actions.c \
		utils.c \
		write.c \
		check.c \
		time.c \
		init.c

OBJS = $(addprefix $(DIR_O)/,$(SRCS:.c=.o))

NAME = philo_one

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(DIR_O)/%.o: %.c
	mkdir -p objs
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ main.c -o $@

clean:
	rm -rf $(DIR_O)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re
