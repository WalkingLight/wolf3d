# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/27 10:33:15 by rheukelm          #+#    #+#              #
#    Updated: 2017/12/13 09:50:59 by rheukelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NONE = \x1b[0m
OK = \x1b[32;01m
WARN = \x1b[33;01m

NAME = wolf3d
LIB_DIR = libft
FLAGS = -Wall -Werror -Wextra -g
HEADERS = includes

SRCS = 	srcs/main.c	\
		srcs/draw.c \
		srcs/tools.c \
		srcs/raycast.c \
		srcs/key.c 

OBJECTS = $(SRCS:.c=.o)

$(NAME): $(LIB_DIR)/libft.a $(OBJECTS)
	@clang $(FLAGS) -L $(LIB_DIR) -l ft -o $@ $^ -lmlx -framework OpenGl -framework Appkit
	@echo "$(OK)compiling [ $(NAME) ] success$(NONE)"

$(LIB_DIR)/libft.a :
	@$(MAKE) -C $(LIB_DIR)

all: $(NAME)

%.o: %.c $(HEADERS)/ft_wolf3d.h
	@clang $(FLAGS) -I $(HEADERS) -c $< -o $@

bug:
	gcc -Wall -Werror -Wextra -g -L libft -l ft libft/libft.a srcs/main.c srcs/draw.c srcs/tools.c srcs/raycast.c srcs/key.c -lmlx -framework OpenGl -framework Appkit

norm:
	@echo "$(OK)Norminette$(NONE)"
	norminette includes/*.h
	norminette srcs/*.c

clean:
	@rm -f $(OBJECTS)
	@make clean -C $(LIB_DIR)
	@rm -rf $(NAME).DSYM
	@echo "$(WARN)clean complete$(NONE)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)
	@echo "$(WARN)fclean complete$(NONE)"

re: fclean $(NAME) 
