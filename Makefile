NAME	=	so_long
NAME_B	=	so_long_bonus
CC		= 	cc -g #-fsanitize=address -g3
CFLAGS	=	-Wall -Wextra -Werror
MLXFLAGS=   -lmlx -lXext -lX11
SRC		=	src/so_long.c \
			src/parsing.c \
			src/get_next_line.c \
			src/errors.c \
			src/so_long_utils.c \
			src/rendring.c \
			src/initialize.c \
			src/check_move.c \
			src/parse_elements.c \
			src/parsing_utils.c
SRC_B	=	src_bonus/so_long_bonus.c \
			src_bonus/parsing.c \
			src/errors.c \
			src/get_next_line.c \
			src_bonus/so_long_utils.c \
			src_bonus/check_moves.c \
			src_bonus/rendering.c \
			src_bonus/rendering2.c \
			src_bonus/parse_map_elem.c \
			src_bonus/parsing_utils.c \
			src_bonus/enemy_move.c
HEADER	=	so_long.h
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

$(NAME): $(OBJ) $(HEADER)
	@$(MAKE) -s -C $(LIBFT_D)
	@$(MAKE) -s -C $(PRINTF_D)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) $(MLXFLAGS) -o $(NAME)
	@echo "compiled successfully ✅"

bonus: $(NAME_B)

$(NAME_B): $(OBJ_B) $(HEADER)
	@$(MAKE) -s -C $(LIBFT_D)
	@$(MAKE) -s -C $(PRINTF_D)
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) $(PRINTF) $(MLXFLAGS) -o $(NAME_B)
	@echo "bonus compiled successfully ✅"

clean:
	@$(MAKE) $(CLEAN) -s -C $(LIBFT_D)
	@$(RM) $(OBJ) $(OBJ_B)

fclean: clean
	@$(MAKE) $(FCLEAN) -s -C $(LIBFT_D)
	@$(RM) $(NAME) $(NAME_B)

re: fclean all

.PHONEY: all clean fclean re bonus

.SECONDARY: