NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -fr
MAIN = cub3d.c
FILES = Utils/loading.c Utils/validating.c Utils/flood_fill_cub3d.c Utils/destroying.c Utils/error_handling.c cub3d.c #Utils/keys.c Utils/utils.c
OBJ_SRC = loading.o validating.o flood_fill_cub3d.o destroying.o error_handling.o cub3d.o #keys.o utils.o
OBJ = obj/loading.o obj/validating.o obj/flood_fill_cub3d.o obj/destroying.o obj/error_handling.o obj/cub3d.o #obj/keys.o obj/utils.o
LIBFT = ./libft
MINILIBX = mlx/minilibx-linux
MLXFLAGS = -lmlx -lXext -lX11
WBLOCK = --no-print-directory

all: $(NAME)

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./include/mlx
	make -C ./include/mlx

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -L $(LIBFT) -lft -L $(MINILIBX) $(MLXFLAGS) -o $(NAME)

$(OBJ): $(MAIN) $(FILES)
	@mkdir -p mlx
	@tar -xzf minilibx-linux.tgz -C mlx
	@make -C $(MINILIBX) -s
	@make $(WBLOCK) -C $(LIBFT) all
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $(FILES)
	@mv $(OBJ_SRC) obj/

clean:
	@$(RM) $(OBJ) obj
	@make $(WBLOCK) clean -C $(LIBFT)
	@make clean -C $(MINILIBX) -s

fclean:
	@$(RM) $(OBJ) $(NAME) obj
	@make $(WBLOCK) fclean -C $(LIBFT)
	@make clean -C $(MINILIBX) -s
	@$(RM) mlx

re: fclean all

.PHONY: all clean fclean re