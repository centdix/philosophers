DIR_O = objs

SRCS = actions.c \
		utils.c \
		utils2.c \
		start_utils.c \
		write_utils.c

OBJS = $(addprefix $(DIR_O)/,$(SRCS:.c=.o))

NAME = philo_three

CC = gcc

CFLAGS = -Wall -Werror -Wextra

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
