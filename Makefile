SRCS = Minishell.c parsing.c split.c strings.c error.c add_space.c qoutes.c
INC = minishell.h
NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
OBJS = $(addprefix obj/, $(SRCS:.c=.o))

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -lreadline -o ${NAME}

obj/%.o: %.c ${INC}
	@mkdir -p $(dir $@)
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: clean
