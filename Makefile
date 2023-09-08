SRCS			= main.c utils.c redirect.c
BONUS_SRCS		= next_line_utils.c next_line.c

OBJS			= $(SRCS:.c=.o)
BONUS_OBJS		= $(BONUS_SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Llibft -lft
OFLAGS			= -I libft -Wall -Wextra -Werror -g
libft			= libft/libft.a

NAME			= pipex

all:			$(NAME)

$(libft):
				make -C libft

$(NAME):		$(OBJS) $(BONUS_OBJS) | $(libft)
				$(CC) -o $(NAME) $(OBJS) $(BONUS_OBJS) $(CFLAGS)

%.o : %.c
				$(CC) $(OFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)
				make -C libft clean

fclean:			clean
				$(RM) $(NAME)
				make -C libft fclean

bonus:			$(OBJS) $(BONUS_OBJS) | $(libft)
				$(CC) -o $(NAME) $(OBJS) $(BONUS_OBJS) $(CFLAGS)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
