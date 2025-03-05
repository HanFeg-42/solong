NAME	=	so_long
CC		= 	cc -g3 #-fsanitize=address -g3
CFLAGS	=	-Wall -Wextra -Werror
MLXFLAGS=   -lmlx -lXext -lX11
SRC		=	src/so_long.c \
			src/parsing.c \
			src/get_next_line.c \
			src/errors.c \
			src/so_long_utils.c \
			src/rendring.c \
			src/initialize.c \
			src/check_move.c
LIBMLX	=	minilibx-linux/libmlx_Linux.a
LMLX	=	minilibx-linux/libmlx.a
OBJ		=	${SRC:.c=.o}
OBJ_B	=	${SRC_B:.c=.o}
LIBFT_D	=	./libft
LIBFT	=	libft/libft.a
PRINTF_D=	./ft_printf
PRINTF	=	ft_printf/ft_printf.a
CLEAN	=	clean
FCLEAN	=	fclean

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -s -C $(LIBFT_D)
	@$(MAKE) -s -C $(PRINTF_D)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) $(MLXFLAGS) -o $(NAME)
	@echo "compiled successfully ✅"

clean:
	@$(MAKE) $(CLEAN) -s -C $(LIBFT_D)
	@$(RM) $(OBJ) $(OBJ_B)

fclean: clean
	@$(MAKE) $(FCLEAN) -s -C $(LIBFT_D)
	@$(RM) $(NAME) $(NAME_B)

re: fclean all

.PHONEY: all clean fclean re bonus