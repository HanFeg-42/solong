NAME	=	so_long
CC		= 	cc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3
MLXFLAGS=   -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
SRC		=	src/so_long.c src/parsing.c src/get_next_line.c src/errors.c
# LIBFT	=	libft/libft.a
# LIBMLX	=	minilibx-linux/libmlx_Linux.a

# %.o: %.c
# 	$(CC) $(CFLAGS) $(MLXFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

# $(NAME): $(OBJ)
#	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
OBJ		=	${SRC:.c=.o}
OBJ_B	=	${SRC_B:.c=.o}
LIBFT_D	=	./libft
LIBFT	=	libft/libft.a
CLEAN	=	clean
FCLEAN	=	fclean

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
all: $(NAME)
$(NAME): $(OBJ)
	@$(MAKE) -s -C $(LIBFT_D)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "compiled successfully ✅"
bonus: $(NAME_B)
$(NAME_B): $(OBJ_B)
	@$(MAKE) -s -C $(LIBFT_D)
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) -o $(NAME_B)
	@echo "bonus compiled successfully ✅"
clean:
	@$(MAKE) $(CLEAN) -s -C $(LIBFT_D)
	@$(RM) $(OBJ) $(OBJ_B)
fclean: clean
	@$(MAKE) $(FCLEAN) -s -C $(LIBFT_D)
	@$(RM) $(NAME) $(NAME_B)
re: fclean all
.PHONEY: all clean fclean re bonus