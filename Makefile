##
## EPITECH PROJECT, 2024
## Plazza
## File description:
## Makefile
##

#-------------- Main Variables --------------#

SRC			=	main.cpp									\

TRUE_SRC 	= 	$(patsubst %,src/%, $(SRC))

OBJ			=	$(TRUE_SRC:.cpp=.o)

NAME		=	plazza

WARNINGS	=	-Wall -Wextra -Wshadow

INCLUDE		=	-I./include

VALGRIND	=	-g3

LIBS		=

CXXFLAGS	=	$(INCLUDE) $(WARNINGS)

#-------------- Tests Variables --------------#

TEST_SRC		=	mainTests.cpp							\

TESTS_LIBS		= 	-lcriterion

TESTS_INCLUDE 		= -I./tests/include -I./include

TESTS_COMPILATION_FLAGS	=	--coverage

TEST_TRUE_SRC	=	$(patsubst %,tests/src/%, $(TEST_SRC))	\
					$(filter-out src/main.cpp, $(TRUE_SRC))

TESTS_FLAGS		=	$(TESTS_INCLUDE) $(WARNINGS) $(TESTS_COMPILATION_FLAGS) $(TESTS_LIBS)

#-------------- Phony & Silent Rules --------------#

.PHONY: all clean fclean re tests_run tests_compile tests_launch

.SILENT: clean fclean re tests_launch tests_run

#-------------- Rules --------------#

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)
	@if [ -f $(NAME) ]; then \
		printf "\033[1;32mCompilation completed ✅\033[0m\n"; \
	else \
		printf "\033[1;31mCompilation failed ❌\033[0m\n"; \
	fi

clean:
	rm -f $(OBJ)
	printf "\033[1;35mObject files removed ✅\033[0m\n"

fclean:	clean
	rm -f $(NAME)
	rm -f unit_tests*
	rm -f *.gc*
	rm -f vgcore*
	rm -f *.so
	printf "\033[1;35mFiles removed ✅\033[0m\n"

re:	fclean all
	printf "\033[1;35mRecompiled ✅\033[0m\n"

#-------------- Tests --------------#

tests_compile: fclean
	g++ -o unit_tests $(TEST_TRUE_SRC) $(TESTS_FLAGS)
	@if [ -f unit_tests ]; then \
		printf "\033[1;32mTests compiled ✅\033[0m\n"; \
	else \
		printf "\033[1;31mTests compilation failed ❌\033[0m\n"; \
	fi

tests_launch:
	./unit_tests
	printf "\033[1;35mTests launched ✅\033[0m\n"
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches
	printf "\033[1;35mCoverage generated ✅\033[0m\n"

tests_run: tests_compile tests_launch
	printf "\033[1;32mTests runned ✅\033[0m\n"
