# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rheukelm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/27 10:33:15 by rheukelm          #+#    #+#              #
#    Updated: 2017/06/27 10:33:22 by rheukelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NONE = \x1b[0m
OK = \x1b[32;01m
WARN = \x1b[33;01m

NAME = wolf3d
LIB_DIR = libft
FLAGS = -Wall -Werror -Wextra
HEADERS = includes

SRCS = 	srcs/main.c	\
		srcs/draw.c \
		srcs/tools.c \
		srcs/raycast.c \
		srcs/key.c 

OBJECTS = $(SRCS:.c=.o)

$(NAME): $(LIB_DIR)/libft.a $(OBJECTS)
	@$gcc $(FLAGS) -L $(LIB_DIR) -l ft -o $@ $^ -lmlx -framework OpenGl -framework Appkit
	@echo "$(OK)compiling [ $(NAME) ] success$(NONE)"

$(LIB_DIR)/libft.a :
	@$(MAKE) -C $(LIB_DIR)

all: $(NAME)

%.o: %.c $(HEADERS)/ft_wolf3d.h
	@$gcc $(FLAGS) -I $(HEADERS) -c $< -o $@

norm:
	@echo "$(OK)Norminette$(NONE)"
	norminette includes/*.h
	norminette srcs/*.c

clean:
	@rm -f $(OBJECTS)
	@make clean -C $(LIB_DIR)
	@echo "$(WARN)clean complete$(NONE)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)
	@echo "$(WARN)fclean complete$(NONE)"

re: fclean $(NAME) 
