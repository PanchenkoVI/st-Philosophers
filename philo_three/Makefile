NAME = philo_three

FL = gcc -Wall -Werror -Wextra -lpthread

WU = ./utils/
WO = ./srcs/

U1 = $(WU)utuls1.c $(WU)utuls2.c 

O1 = $(WO)main.c $(WO)parser.c $(WO)print_line.c $(WO)tred.c \
	$(WO)crcl.c $(WO)clear.c

SRCS = $(O1) $(U1)

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(FL) $(SRCS) -o $(NAME)
	@echo "\033[32mCompilation $(NAME): OK\033[0m"

clean:
	@rm -f $(OBJS)
	@echo "\033[32mDeletion: OK\033[0m" 

fclean: clean
	@rm -rf philo_three.dSYM
	@rm -f $(NAME)

re: fclean all

test1:
	./$(NAME) 5 800 200 200	

test2:
	./$(NAME) 5 800 200 200 1

test3:
	./$(NAME) 4 410 200 200

test4:
	./$(NAME) 4 310 200 100 

test5:
	./$(NAME) 5 800 200 200 1 | grep -i "is eating" | wc -l

test6:
	./$(NAME) 5 800 200 200 7 | grep -i "is eating" | wc -l

test7:
	./$(NAME) 2 800 200 200 1

.PHONY: all clean fclean re