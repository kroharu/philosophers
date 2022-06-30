SRCS		=	${wildcard *.c}		\

OBJS		=	$(SRCS:.c=.o)	

B_OBJS		=	$(B_SRCS:.c=.o)	

HEADS		=	${wildcard *.h}

NAME		=	philo

GCC			=	gcc -MMD -Wall -Wextra -Werror

RM			=	rm -f

%.o: 		%.c
			$(GCC) -c $< -o $@

$(NAME):	$(HEADS) $(OBJS)
			$(GCC) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(wildcard *.d)
			$(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re