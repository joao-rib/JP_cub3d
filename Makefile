NAME = so_long
BONUS_NAME = so_long_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -fr
MAIN = so_long.c
BONUS = so_long_bonus.c
SRC = libft/*.c ft_printf/*.c Utils/*.c
OBJ = obj/*.o
MINILIBX = mlx/minilibx-linux
MLXFLAGS = -lmlx -lXext -lX11
BONUS_SRC = libft/*.c ft_printf/*.c Bonus/*.c
BONUS_OBJ = obj_bonus/*.o

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -L $(MINILIBX) $(MLXFLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	@$(CC) $(FLAGS) $(BONUS_OBJ) -L $(MINILIBX) $(MLXFLAGS) -o $(BONUS_NAME)

$(OBJ): $(MAIN) $(SRC)
	@mkdir -p mlx
	@tar -xzf minilibx-linux.tgz -C mlx
	@make -C $(MINILIBX) -s
	@mkdir -p obj
	@$(CC) $(FLAGS) -c $(SRC) $(MAIN)
	@mv *.o obj/

$(BONUS_OBJ): $(BONUS) $(BONUS_SRC)
	@mkdir -p mlx
	@tar -xzf minilibx-linux.tgz -C mlx
	@make -C $(MINILIBX) -s
	@mkdir -p obj_bonus
	@$(CC) $(FLAGS) -c $(BONUS_SRC) $(BONUS)
	@mv *.o obj_bonus/

clean:
	@$(RM) $(OBJ) $(BONUS_OBJ) obj obj_bonus
	@make clean -C $(MINILIBX) -s

fclean:
	@$(RM) $(OBJ) $(BONUS_OBJ) $(NAME) $(BONUS_NAME) obj obj_bonus
	@make clean -C $(MINILIBX) -s
	@$(RM) mlx

re: fclean all

bonus_re: fclean bonus