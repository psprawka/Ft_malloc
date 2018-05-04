# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psprawka <psprawka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/09 23:21:55 by psprawka          #+#    #+#              #
#    Updated: 2018/03/08 07:14:00 by psprawka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_malloc
ENAME = FT_MALLOC
FLAGS = -g -Wall -Wextra -Werror

HEADERS = includes/
SRCS_DIR = srcs/

SRCS =	$(SRCS_DIR)malloc.c \
	$(SRCS_DIR)malloc_tags.c \
	$(SRCS_DIR)malloc_rotations.c \
	$(SRCS_DIR)malloc_tools.c \
	$(SRCS_DIR)tree_insertion.c

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

BUILD_PRINT = @echo "\r\033[K\033[0;38;5;206m[$(ENAME)] \033[38;5;80mBuilding $<"
DONE = @echo "\033[K\033[1;38;5;200m$(ENAME) ready to use!"
CLEAN_O = @echo "\033[38;5;246mObject files removed! [$(ENAME)]"
CLEAN_A = @echo "\033[38;5;246mExecutable removed! [$(ENAME)]"

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJS) $(HEADERS)
	@gcc $(FLAGS) -I $(HEADERS) $(OBJS) $(LIBFT) -lncurses -o $(NAME)
	$(DONE)

$(LIBFT):
	@make -C libft
	@echo ""

%.o: %.c
	$(BUILD_PRINT)
	@gcc $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@$(MAKE) -C libft/ clean
	@rm -f $(OBJS)
	$(CLEAN_O)

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME)
	$(CLEAN_A)

re: fclean all
