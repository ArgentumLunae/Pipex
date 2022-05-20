# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/07/21 12:25:06 by mteerlin      #+#    #+#                  #
#    Updated: 2022/05/15 16:05:37 by mteerlin      ########   odam.nl          #
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

FTPRINTF_DIR := $(INCL_DIR)ft_printf/
FTPRINTF	:= $(FTPRINTF_DIR)libftprintf.a

AR		?= ar rcs;
SANFLAGS ?= -fsanitize=address -g
CFLAGS	?= -Wall -Wextra -Werror

all: 		$(NAME)

$(NAME):	$(FTPRINTF) $(OBJ)
			@echo "Compiling pipex."
			@$(CC) $(CFLAGS) $(FTPRINTF) $(OBJ) -o $(NAME)
#			@$(CC) $(CFLAGS) -L$(LIBFT_DIR) $(OBJ) -lft -o $(NAME)
			@echo "Compilation finished."

$(FTPRINTF):
			@echo "Making library libft."
			@$(MAKE) --no-print-directory -C $(FTPRINTF_DIR)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c $(HDR_DIR)$(HDR)
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@echo "Removing object files"
			@rm -f $(OBJ_DIR)*.o $(LIBFT_DIR)*.o $(FTPRINTF_DIR)/src/*.o
			@rmdir -p $(OBJ_DIR)

fclean:
			@$(MAKE) --no-print-directory clean
			@echo "Removing excecutables"
			@rm -f $(NAME) $(LIBFT) $(FTPRINTF)
re:
			@$(MAKE) --no-print-directory fclean
			@$(MAKE) --no-print-directory all