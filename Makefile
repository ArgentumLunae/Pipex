# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/21 12:25:06 by mteerlin      #+#    #+#                  #
#    Updated: 2022/07/21 14:30:06 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include sources.mk

NAME	= pipex

INCL_DIR := incl/
HDR_DIR := hdr/
HDR		:= pipex.h
SRC_DIR := src/

OBJ_DIR := obj/
OBJ		:= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIBFT_DIR := $(INCL_DIR)libft/
LIBFT := $(LIBFT_DIR)libft.a

AR		?= ar rcs;
SANFLAGS ?= -fsanitize=address -g
CFLAGS	?= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
			@echo "Compiling pipex."
			@$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)
			@echo "Compilation finished."

$(LIBFT):
			@echo "Making library libft."
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c $(HDR_DIR)$(HDR)
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@echo "Removing object files"
			@rm -f $(OBJ_DIR)*.o $(LIBFT_DIR)*.o
			@rmdir -p $(OBJ_DIR)

fclean:
			@$(MAKE) --no-print-directory clean
			@echo "Removing excecutables"
			@rm -f $(NAME) $(LIBFT)
re:
			@$(MAKE) --no-print-directory fclean
			@$(MAKE) --no-print-directory all