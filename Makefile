CC := cc
CFLAGS := -lmlx -lXext -lX11

NAME := fdf
LIBFT := libft/libft.a

SRC := $(wildcard *.c)

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) ~/.local/lib/libmlx.a $(LIBFT) -o $@

$(LIBFT):
	make -C libft/

fclean:
	rm -f $(NAME)

re: fclean all

:PHONY all fclean re
