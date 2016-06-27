# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/21 19:14:13 by mrbanane          #+#    #+#              #
#    Updated: 2015/06/03 17:10:42 by rdantzer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME= rt

#TODO remove wildcard
SRC= *.c

OBJ= $(SRC:.c=.o)

CC= gcc
RM= rm -rf

CFLAGS= -Wall -Werror -Wextra -O2

SDL_2_CFLAGS= $(shell sdl2-config --cflags)
SDL_2_LIBS= $(shell sdl2-config --libs)

## Aesthetics
RED= \033[34m
GREEN= \033[32m
RESET= \033[0m

all: $(NAME)

$(NAME):
	@make -C ./libft
	@printf "$(RED)[$(NAME)] Compiling sources...$(RESET)\t\t"
	@$(CC) $(CFLAGS) -c -I ./inc -I ./libft/includes $(SDL_2_CFLAGS) $(SRC)
	@$(CC) $(CFLAGS) $(OBJ) -L./libft -lft $(SDL_2_LIBS) -o $(NAME)
	@$(RM) $(OBJ)
	@printf "$(GREEN)Done$(RESET)\n"

clean:
	@printf "$(RED)[$(NAME)] Removing objects...$(RESET)\t\t"
	@$(RM) $(OBJ)
	@printf "$(GREEN)Done$(RESET)\n"

fclean:	clean
	@printf "$(RED)[$(NAME)] Removing $(NAME)...$(RESET)\t\t"
	@$(RM) $(NAME)
	@printf "$(GREEN)Done$(RESET)\n"

re: fclean all
