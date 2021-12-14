NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
THREAD	= -lpthread

SRCS	= main.c \
		init.c \
		utils.c \
		ft_atoi.c \
		start_philo.c
OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(THREAD) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c 
	$(CC) $(CFLAGS) -c $<  -o $(<:.c=.o)

.PHONY:	all clean fclean re
