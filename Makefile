SRCS			= main.c utils.c get_next_line_utils.c get_next_line.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Llibft -lft
OFLAGS			= -I libft -Wall -Wextra -Werror -g
libft			= libft/libft.a

NAME			= pipex

all:			$(NAME)

$(libft):
				make -C libft

$(NAME):		$(OBJS) | $(libft)
				$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

%.o : %.c
				$(CC) $(OFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)
				make -C libft clean

fclean:			clean
				$(RM) $(NAME)
				make -C libft fclean

re:				fclean $(NAME)

.PHONY:			all clean fclean re
