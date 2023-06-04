# SRCS			= main.c utils.c
# OBJS			= $(SRCS:.c=.o)

# CC				= gcc
# RM				= rm -f
# CFLAGS			= -Llibft -lft
# OFLAGS			= -I libft -Wall -Wextra -Werror
# libft			= libft/libft.a

# NAME			= pipex

# all:			$(NAME)

# $(libft):
# 				make -C libft

# $(NAME):		$(OBJS) $(libft)
# 				$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

# %.o : %.c
# 				$(CC) $(OFLAGS) -c $< -o $@

# clean:
# 				$(RM) $(OBJS)

# fclean:			clean
# 				$(RM) $(NAME)

# re:				fclean $(NAME)

# # bonus:			$(OBJS)
# # 				cc -o $(NAME) $(OBJS)

# .PHONY:			all clean fclean re
SRCS			= main.c utils.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Llibft -lft
OFLAGS			= -I libft -Wall -Wextra -Werror
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