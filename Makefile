NAME            = so_long

CC              = cc
CFLAGS          = -Wall -Wextra -Werror
AR              = ar
ARFLAGS         = rcs
RM              = rm -rf

SRC             = src/game_exit.c								\
                  src/game_graphics.c							\
                  src/game_main.c								\
                  src/game_map_create.c							\
                  src/game_map_validation.c						\
                  src/game_player_controls.c					\
                  library/GetNextLine/get_next_line.c			\
                  library/GetNextLine/get_next_line_utils.c

OBJ             = $(SRC:.c=.o)

LIBFT_PATH      = ./library/Libft
LIBFT           = $(LIBFT_PATH)/libft.a

PRINTF_PATH     = ./library/Ft_Printf
PRINTF          = $(PRINTF_PATH)/libftprintf.a

MINILIBX_PATH   = ./library/minilibx-linux
MLX             = $(MINILIBX_PATH)/libmlx.a

LIBS            = -L$(MINILIBX_PATH) -lmlx -L/usr/X11/lib -lX11 -lXext

all:            $(NAME)

$(NAME):        $(OBJ) $(LIBFT) $(PRINTF) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF) $(LIBS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(PRINTF):
	@make -C $(PRINTF_PATH) all

$(MLX):
	@make -C $(MINILIBX_PATH) all

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(PRINTF_PATH) clean
	@make -C $(MINILIBX_PATH) clean
	@$(RM) $(OBJ)

fclean:         clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(PRINTF_PATH) fclean
	@$(RM) $(NAME)

re:             fclean all

.PHONY:         all clean fclean re