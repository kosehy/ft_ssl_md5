# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sko <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/04 16:15:27 by sko               #+#    #+#              #
#    Updated: 2019/11/25 19:59:44 by sko              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRC_PATH = srcs/
SRCS = *.c

SRC = $(addprefix $(SRC_PATH), $(SRCS))

FT = libft/
LIBFT = libft.a
HEAD = ./includes
OBJ = *.o
FLAG = -Wextra -Werror -Wall
DEL = rm -rf

all: $(NAME)

$(NAME):
	@make -C $(FT)
	@gcc $(FLAG) -o $(NAME) $(SRC) -I $(HEAD) -I $(FT) -L. $(FT)$(LIBFT) -g
	@echo "[=================]"
	@echo "|     success !   |"
	@echo "|     libft.a     |"
	@echo "|   was summoned  |"
	@echo "[=================]"

clean:
	@$(DEL) $(OBJ)
	@make -C $(FT) clean
	@echo "[=================]"
	@echo "|     succes !    |"
	@echo "|     XXXXX.o     |"
	@echo "|  was destroyed  |"
	@echo "[=================]"

fclean:	clean
	@$(DEL) $(NAME)
	@make -C $(FT) fclean
	@echo "[=================]"
	@echo "|     succes !    |"
	@echo "|     libft.a     |"
	@echo "|  was destroyed  |"
	@echo "[=================]"

re: fclean all

debug:
	gcc -g -o $(NAME) $(SRC) -I $(HEAD)
