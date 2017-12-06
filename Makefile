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
	@echo "compiling [ $(NAME) ] success"

$(LIB_DIR)/libft.a :
	@$(MAKE) -C $(LIB_DIR)

all: $(NAME)

%.o: %.c $(HEADERS)/ft_wolf3d.h
	@$gcc $(FLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@make clean -C $(LIB_DIR)
	@echo "clean complete"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)
	@echo "fclean complete"

re: fclean $(NAME) 
