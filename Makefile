#Compiler Options
C_FLAGS = -Wall -Wextra -I
#Filenames
LIBFT_DIR := printf/
LIBFT := printf/libftprintf.a
HEADERS := includes/*.h
INC_DIR := includes/
NAME := lem-in
VISIO := visu-hex
VIS_DIR := visualization/
SRCS_DIR := src
SRCS_FILES := main_validation.c create_links.c pars_hex.c pars_utils.c structure_init.c structure_init_2.c\
		hash_function.c hash_utils.c make_free.c validate_rooms.c structure_init_1.c structure_init_3.c\
		validate_rooms_01.c ants.c copy_stuff.c count_paths.c destroy.c display_stuff.c distribute_ants.c\
		flow.c generic_list.c get_stuff.c jam.c node_stack.c node.c path_list.c path.c pathfinder_improved.c\
		pathfinder.c plug.c reset.c saturate.c stack.c superimpose_backwards.c superimpose_forwards.c superimpose.c\
		support.c undo_flow.c waste_of_time.c run.c run_extra_functions.c
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJECTS := $(SRCS:.c=.o)
HEADER = libft/libft.h

all: $(LIBFT) $(NAME) $(VISIO)

$(NAME): $(OBJECTS)
	gcc -o $(NAME) $(OBJECTS) -L$(LIBFT_DIR) -lftprintf

.FORCE:

$(VISIO):
	make -C $(VIS_DIR)
	cp $(VIS_DIR)$(VISIO) .

$(LIBFT):.FORCE
	make -C $(LIBFT_DIR)	

$(OBJECTS): %.o: %.c $(HEADERS)
	gcc $(C_FLAGS) $(INC_DIR) -o $@ -c $<

clean:
	make clean -C $(VIS_DIR)
	make clean -C $(LIBFT_DIR)
	/bin/rm -f $(OBJECTS)
fclean: clean
	make fclean -C $(VIS_DIR)
	make fclean -C $(LIBFT_DIR)
	/bin/rm -f $(NAME)
	/bin/rm -f $(VISIO)
re: fclean all

