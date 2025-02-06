NAME			=	so_long

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS 		=	rcs
RM				=	rm -rf

SRC				=	file_control.c								\
					map_read.c									\
					main.c 										\
					map_positions.c								\
					player_control.c							\
					texture.c									\
					library/GetNextLine/get_next_line.c 		\
					library/GetNextLine/get_next_line_utils.c 	

LIBFT_PATH		=	./library/Libft
LIBFT			=	$(LIBFT_PATH)/libft.a

PRINTF_PATH		=	./library/Ft_Printf
PRINTF			=	$(PRINTF_PATH)/libftprintf.a

MINILIBX_PATH	=	./library/minilibx-linux

# BSD için libGL ve X11 yolları
LIBS = -lmlx -L/usr/X11/lib -lX11 -lXext  

all:				$(NAME)

$(NAME):			$(LIBFT) $(PRINTF) mlx
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT) $(PRINTF) -L$(MINILIBX_PATH) $(LIBS)

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(PRINTF):
	@make -C $(PRINTF_PATH) all

mlx:
	@make -C $(MINILIBX_PATH) all

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(MINILIBX_PATH) clean
	@make -C $(PRINTF_PATH) clean

fclean:				clean
	@make -C $(LIBFT_PATH) fclean
	@make -C $(PRINTF_PATH) fclean
	@$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re libft printf
