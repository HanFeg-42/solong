NAME	=	so_long
CC		= 	cc
CFLAGS	=	-Wall -Wextra -Werror
MLCFLAGS=   -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
SRC		=	src/so_long.c parsing/parsing.c
LIBFT	=	libft/libft.a
LIBMLX	=	minilibx-linux/libmlx_Linux.a