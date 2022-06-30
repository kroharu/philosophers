B_SRCS		=	${wildcard *.c}	\

B_OBJS		=	$(B_SRCS:.c=.o)	

B_HEADS		=	${wildcard *.h}

B_NAME		=	philo_bonus

GCC			=	gcc -MMD -Wall -Wextra -Werror

RM			=	rm -f

%.o: 		%.c
			$(GCC) -c $< -o $@

$(B_NAME):	$(B_HEADS) $(B_OBJS)
			$(GCC) $(B_OBJS) -o $(B_NAME)
			

all:		$(B_NAME)

bonus:		$(B_NAME)

clean:
			$(RM) $(wildcard *.d)
			$(RM) $(B_OBJS)

fclean: 	clean
			$(RM) $(B_NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re