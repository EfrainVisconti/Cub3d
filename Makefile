# Coder Alias
USER_NAME      = eviscont & jde-orma 

#Colors:

DEF_COLOR	   = \033[0;39m
BLUE		   = \033[0;94m
PURPLE         = \033[0;95m
GREEN		   = \033[0;92m

# Compiler and flags
CC             = gcc
CFLAGS         = -Wall -Wextra -Werror -I $(INC_DIR) -I $(MINILIBX_DIR) -I $(LIBFT_DIR)/include -O3 -g3
LINKING        = -lmlx_Linux -lXext -lX11 -lm

# Directories
SRC_DIR        = source/
INC_DIR        = source/
LIBFT_DIR      = libraries/libft/
MINILIBX_DIR   = libraries/minilibx-linux/
OBJ_DIR        = source/
BIN_DIR        = ./

# Source files
SRC_FILE       = main.c game.c raycasting.c textures.c draw.c move.c
			     
SRC            = $(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ_FILE       = $(SRC_FILE:.c=.o)
OBJ            = $(addprefix $(OBJ_DIR), $(OBJ_FILE))

# Binary name for your program
CODE_BIN       = $(BIN_DIR)cub3d

# Static library
LIBFT          = $(LIBFT_DIR)libft.a
MINILIBX       = $(MINILIBX_DIR)libmlx.a

# Output executable
NAME           = cub3D

# Variable to control if the library has been built
LIBFT_BUILT    = no
MINILIBX_BUILT = no

all: $(CODE_BIN)

$(CODE_BIN): $(LIBFT) $(MINILIBX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L/usr/lib -L$(MINILIBX_DIR) $(LINKING) -o $@
	@echo "$(GREEN)✔ $(BLUE)$(USER_NAME)'s $(PURPLE)$(NAME)$(BLUE) compilation$(DEF_COLOR)"

$(LIBFT):
	@if [ "$(LIBFT_BUILT)" = "no" ]; then \
		$(MAKE) -C $(LIBFT_DIR); \
		LIBFT_BUILT=yes; \
	fi

$(MINILIBX):
	@if [ "$(MINILIBX_BUILT)" = "no" ]; then \
		$(MAKE) -C $(MINILIBX_DIR); \
		MINILIBX_BUILT=yes; \
	fi

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "$(GREEN)✔ $(BLUE)$(USER_NAME)'s $(PURPLE)$(NAME)$(BLUE) .o files removal$(DEF_COLOR)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MINILIBX_DIR) clean

fclean: clean
	@$(RM) $(CODE_BIN)
	@echo "$(GREEN)✔ $(BLUE)$(USER_NAME)'s $(PURPLE)$(NAME)$(BLUE) executable file and .o files removal$(DEF_COLOR)"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
