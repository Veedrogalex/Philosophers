NAME 			= philo_bonus

HEADER			= philo_bonus.h

SRCS			=	args_bonus.c\
					init_and_mem_bonus.c\
					timex_bonus.c\
					philo_bonus.c\
					printer_bonus.c\
					checkers.c

OBJS			= $(SRCS:.c=.o)
%.o:			%.c ${HEADER}
				$(CC) $(CFLAGS) -c -o $@ $<

RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra -g
INCLUDES		= ./philo.h

$(NAME):		$(OBJS) $(HEADER)
				gcc $(OBJS) -o ${NAME}

all:			$(NAME)
clean:
				$(RM) $(OBJS)		

fclean:			clean
				$(RM) $(NAME)
				
re:				fclean all
test:			all
.PHONY:			all clean fclean re