# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/14 17:07:06 by aollivie          #+#    #+#              #
#    Updated: 2017/11/27 23:04:56 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


DEBUG=yes
CC=clang

ifeq ($(DEBUG), yes)
				CFLAGS=  -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -O1 -g #-fsanitize=address -fno-omit-frame-pointer # -g -fsanitize=address,undefined # -g -ansi -pedantic
else
		CFLAGS=  -Wall -Wextra -Werror
endif

NAME_SERVER = server

NAME_CLIENT = client

LIBFT =libft/libft.a



I_DIR= -I inc/ -I libft/inc

ifeq ($(LANG),fr)
	I_DIR= -I inc/ -I./libft/inc
endif

O_DIR= obj

MKDIR = mkdir

CLIENT_SRC =
SERVER_SRC =

C_SRC = main.c buffer_circulaire.c chanel.c create_server.c process.c tool.c 

VPATH= .:src:src/client:src/server

OBJS= $(C_SRC:%.c=$(O_DIR)/%.o) $(CLIENT_SRC:%.c=$(O_DIR)/%.o) \
 		$(SERVER_SRC:%.c=$(O_DIR)/%.o)

.PHONY : all clean fclean re

all :
	make -C libft
	make -j $(NAME_SERVER)
	# make -j $(NAME_CLIENT)

ifeq ($(DEBUG),yes)
				@echo "Generation mode debug"
else
				@echo "Generation mode release"
endif

$(NAME_SERVER):$(OBJS)
				$(CC) $(CFLAGS) $(I_DIR) $^  $(LIBFT) -o $@

$(NAME_CLIENT):$(OBJS)
		$(CC) $(CFLAGS) $(I_DIR) $^  $(LIBFT) -o $@

$(O_DIR)/%.o: %.c
				$(CC) $(CFLAGS) $(I_DIR) -c $< -o $@

$(OBJS): | $(O_DIR)

$(O_DIR):
				$(MKDIR) $(O_DIR)
clean :
		rm -rf $(O_DIR)
		make clean -C libft

fclean : clean
		@rm -rf $(NAME_SERVER) $(NAME_CLIENT)
		make fclean -C libft

re : fclean all
