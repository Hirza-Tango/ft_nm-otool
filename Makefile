NM=ft_nm
OTOOL=ft_otool
DEPS=libft/libft.a ft_printf/libftprintf.a
LIBFT_DIR=libft
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I . -I $(INCLUDES) -O0 -g
CFILES= main.c file_handle.c endian.c
NM_FILES=ft_nm.c
OTOOL_FILES=ft_otool.c
OBJ=$(CFILES:%.c=build/%.o)
NM_OBJ=$(NM_FILES:%.c=build/%.o)
OTOOL_OBJ=$(OTOOL_FILES:%.c=build/%.o)

all: $(NM) $(OTOOL);

$(OTOOL): $(OBJ) $(OTOOL_OBJ) $(REL_DEPS)
	@$(CC) $(CFLAGS) $^ -o $@

$(NM): $(OBJ) $(NM_OBJ) $(REL_DEPS)
	@$(CC) $(CFLAGS) $^ -o $@

$(REL_DEPS):
	@make -C $(dir $@)

build/%.o: %.c ft_nm_otool.h
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@

clean fclean re::
	@for file in $(dir $(REL_DEPS)) ; do $(MAKE) -C $$file $@ ; done

clean::
	@rm -rf build/

fclean:: clean
	@rm -rf $(NAME) $(LOCAL_NAME)

re:: fclean all

.PHONY: clean fclean re all $(REL_DEPS)
