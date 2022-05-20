# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mteerlin <mteerlin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/18 13:34:08 by mteerlin      #+#    #+#                  #
#    Updated: 2022/05/15 16:07:31 by mteerlin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
AR			= ar rcs
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src/
LIBFT_DIR	= ../libft/

HDR 		= $(HDR_DIR)ft_printf.h
SRC			= ft_printf.c \
			  pf_character.c \
			  pf_parse.c \
			  pf_pointers.c \
			  pf_signed_dec.c \
			  pf_string.c \
			  pf_unsigned_base.c \
			  pf_percentile.c\
			  pf_utils.c
OBJ			= $(SRC:%.c=$(SRC_DIR)%.o)
LIBFT		= $(LIBFT_DIR)libft.a

all: 		$(NAME)

$(NAME): $(LIBFT) $(OBJ)
			@cp $(LIBFT) $(NAME)
			@$(AR) $(NAME) $(OBJ)

$(LIBFT):
			@$(MAKE) -C $(LIBFT_DIR) bonus

%.o: %.c $(HDR_DIR)$(HDR)
			@$(CC) $(CFLAGS) -c -o $@ $<

clean:
			@rm -f $(OBJ) $(LIBFT_DIR)*.o

fclean:
			@$(MAKE) clean
			@rm -f $(NAME)

re:
			@$(MAKE) fclean
			@$(MAKE) all

.PHONY:		all clean fclean re