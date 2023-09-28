SRC		=	main.c \
			error.c \
			atoi.c
CFLAGS	=	-Wall -Werror -Wextra
#CFLAGS	+=	-g -fsanitize=thread
OBJ_F	=	$(SRC:%.c=obj/%.o)
PHILO	=	philo
BRed	=	\033[1;31m
BGreen	=	\033[1;32m
R		=	\033[0m

all : $(PHILO)

$(PHILO) : $(OBJ_F)
	@echo "executable ${BGreen}ready${R}"
	@$(CC) $(CFLAGS) $^ -o $@

obj/%.o : src/%.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $^ -o $@

clean :
	@echo "${BRed}removed${R} object files"
	@rm -rf obj

fclean : clean
	@echo "${BRed}removed${R} executable"
	@rm $(PHILO)

re : fclean all