CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LFLAGFS = -lreadline
RM = rm -rf
NAME = minishell
SRCS = cd.c echo.c env.c exec_helper.c execution.c exit.c export_helper1.c export_helpers.c export.c \
	libft.c linked_list.c main.c pwd.c split.c strings.c unset.c utils.c redirections.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	 $(CC) $(LFLAGFS) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all