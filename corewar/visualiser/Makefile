##
## EPITECH PROJECT, 2023
## Standard File
## File description:
## Makefile
##

NAME = corewar

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

OBJ = $(SRC:.c=.o)

CFLAGS = -I./include -L../lib -lglobal -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../lib/
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	make -C ../lib/ clean
	rm -rf $(OBJ)
	rm -rf *.gcda
	rm -rf *.gcno

fclean: clean
	make -C ../lib/ fclean
	rm -rf $(NAME)

re: fclean all
