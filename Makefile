NAME	=	philo

CC		=	gcc
CFLAGS	=	-I. -pthread -Wall -Wextra #-Werror -fsanitize=address
RM		=	rm

SRCS	=	philo_main.c				\
			srcs/philo_loop.c			\
			srcs/philosophers.c			\
			srcs/time_tools.c			\
			srcs/utils/ft_atoi.c		\
			srcs/utils/ft_isspace.c		\
			srcs/utils/ft_isdigit.c		\
			srcs/errors/bad_param.c		

OBJS	=	${SRCS:.c=.o}

$(NAME):	$(OBJS)
			$(CC) -pthread -g  $(OBJS) -o $(NAME)
			@echo "\033[1;32mme pican loh cocooo\033[0m"

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

DAY		=	$(shell date +)
git:
			git add .
			git commit -m "Authomatic push at: $(DAY)"
			git push

.PHONY:		all clean fclean re git