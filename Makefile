NAME	=	so_long
CC		= 	cc
CFLAGS	=	-Wall -Wextra -Werror
MLXFLAGS=   -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
SRC		=	src/so_long.c parsing/parsing.c
LIBFT	=	libft/libft.a
LIBMLX	=	minilibx-linux/libmlx_Linux.a

%.o: %.c
	$(CC) $(CFLAGS) $(MLXFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
