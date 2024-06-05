##
## EPITECH PROJECT, 2023
## Standard File
## File description:
## Makefile
##

NAME = corewar

NAME_T = unit_tests

SRC = src/main.c \
      src/corewar.c \
      src/game_loop.c \
      src/op.c \
      src/error_handling.c \
      src/read_instruction.c \
      src/swap.c \
      src/instructions/live.c \
      src/instructions/ld.c \
      src/instructions/st.c \
      src/instructions/add.c \
      src/instructions/sub.c \
      src/instructions/and.c \
      src/instructions/or.c \
      src/instructions/xor.c \
      src/instructions/zjmp.c \
      src/instructions/ldi.c \
      src/instructions/sti.c \
      src/instructions/fork.c \
      src/instructions/lld.c \
      src/instructions/lldi.c \
      src/instructions/lfork.c \
      src/instructions/aff.c \

SRC_T = lib/my/my_putchar.c \
        lib/my/my_putstr.c \
        lib/my/my_puterror.c \
        lib/my/my_miniprintf.c \
        lib/my/my_strlen.c \
        lib/my/my_getnbr.c \
        lib/my/my_nbr_to_str.c \
        lib/my/my_power.c \
        lib/my/my_power_float.c \
        lib/my/my_putnbr.c \
        lib/my/my_putfloat.c \
        lib/my/my_putnbr_base.c \
        lib/my/my_stradd.c \
        lib/my/my_strdup.c \
        lib/my/my_strcat.c \
        lib/my/my_strcat_na.c \
        lib/my/my_strcpy.c \
        lib/my/my_strcmp.c \
        lib/my/my_strncmp.c \
        lib/my/my_str_isnum.c \
        lib/my/my_str_to_word_array.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -I./include -L./lib -lglobal

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib/
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

$(NAME_T): fclean
	gcc -o $(NAME_T) $(SRC_T) tests/test_lib.c --coverage \
      -lcriterion

tests_run: $(NAME_T)
	./unit_tests

check_tests: tests_run
	gcovr
	gcovr --branches
	make fclean

clean:
	make -C lib/ clean
	rm -rf $(OBJ)
	rm -rf *.gcda
	rm -rf *.gcno

fclean: clean
	make -C lib/ fclean
	rm -rf $(NAME)
	rm -rf $(NAME_T)

re: fclean all
