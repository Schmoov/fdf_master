CC := cc
CFLAGS := -lmlx -lXext -lX11 -lm

NAME := fdf
LIBFT := libft/libft.a

SRC :=  parser.c main.c

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) ~/.local/lib/libmlx.a $(LIBFT) -o $@

$(LIBFT):
	make -C libft/

fclean:
	rm -f $(NAME)

rfclean: fclean
	make -C libft/ fclean

re: fclean all

:PHONY all fclean re rfclean
