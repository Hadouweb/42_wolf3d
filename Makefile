CC = gcc -Werror -Wextra -Wall -g -pg

SRCPATH = ./srcs
INCPATH = ./includes

LIBFT = ./libft
MINILIBX = ./minilibx_macos

HEADER = -I $(LIBFT)/includes -I $(INCPATH) -I $(MINILIBX)

LIB = -L$(LIBFT) -lft -L$(MINILIBX) -lmlx -framework OpenGL -framework AppKit 

SRC = 	$(SRCPATH)/main.c\
		$(SRCPATH)/w_draw.c\
		$(SRCPATH)/w_event.c\
		$(SRCPATH)/w_error.c\
		$(SRCPATH)/w_set_data.c\
		$(SRCPATH)/w_util.c\
		$(SRCPATH)/w_dda_algorithm.c\
		$(SRCPATH)/w_draw_view.c\
		$(SRCPATH)/w_draw_texture.c\
		$(SRCPATH)/w_player_direction.c\
		$(SRCPATH)/w_set_texture.c\
		$(SRCPATH)/w_set_map.c\
		$(SRCPATH)/w_get_data.c\

OBJ = $(SRC:.c=.o)

NAME = wolf3d

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@make -C $(MINILIBX)
	@$(CC) $(HEADER) $(LIB) -o $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(HEADER) -o $@ -c $<
	@echo "\033[37m█\033[0m\c"

clean : 
	@make -C $(LIBFT) clean
	@make -C $(MINILIBX) clean
	rm -rf $(OBJ)

fclean : clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re