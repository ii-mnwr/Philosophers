CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread -I. -g
SRCS	= philo.c philo_utils_1.c philo_utils_2.c philo_utils_3.c
OBJS	= $(SRCS:.c=.o)
RM		= rm -f
NAME	= philo

all:	 $(NAME)

$(NAME): $(OBJS)
			@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:	clean
			@$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY: all fclean clean re