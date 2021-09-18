NAME 			= philo

HEADER			= philo.h

SRCS			=	args.c init_and_mem.c timex.c philo.c printer.c

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