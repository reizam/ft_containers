NAME			= ft
TEST_NAME		= std
SRCS_PATH		= ./src/
OBJS_PATH		= ./objs/
OBJS_TEST_PATH	= ./objs_test/
SRCSC			= main.cpp

SRCSH			= 
SRCS			= $(addprefix $(SRCS_PATH),$(SRCSC))
OBJS_NAME		= $(SRCSC:%.cpp=%.o)
OBJS 			= $(addprefix $(OBJS_PATH),$(OBJS_NAME))
OBJS_TEST_NAME	= $(SRCSC:%.cpp=%.o)
OBJS_TEST		= $(addprefix $(OBJS_TEST_PATH),$(OBJS_TEST_NAME))
LIBS 		= 
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
CXX			= clang++

all:		${NAME}

$(NAME):	${OBJS} ${SRCSH} ${OBJS_TEST}
			@${CXX} ${CXXFLAGS} ${OBJS} ${LIBS} -o ${NAME}
			@echo "\033[1;33m${NAME} program generated."
			@${CXX} ${CXXFLAGS} ${OBJS_TEST} ${LIBS} -o ${TEST_NAME}
			@echo "\033[1;33m${TEST_NAME} program generated."
			@echo "\n"
			@echo "\033[1;32m-------------------------------"
			@echo "\033[1;32m|    ┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐    |"
			@echo 			"|    └─┐│ ││  │  ├┤ └─┐└─┐    |"
			@echo 			"|    └─┘└─┘└─┘└─┘└─┘└─┘└─┘    |"
			@echo "\033[1;32m-------------------------------\033[0m"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
				@mkdir -p $(OBJS_PATH)
				@clang++ $(CXXFLAGS) -o $@ -c $<
				@echo "\033[1;34m$@ generated."

$(OBJS_TEST_PATH)%.o: $(SRCS_PATH)%.cpp
				@mkdir -p $(OBJS_TEST_PATH)
				@clang++ $(CXXFLAGS) -DFT_VERSION=0 -o $@ -c $<
				@echo "\033[1;34m$@ generated.\033[0m"

test:		all
			@sh test.sh

clean:
			@rm -f ${OBJS}
			@rm -f ${OBJS_TEST}
			@rm -rf ${OBJS_PATH}
			@rm -rf ${OBJS_TEST_PATH}
			@echo "\033[1;31mRemoving .o files\033[0;0m"

fclean:		clean
			@rm -f ${NAME}
			@rm -f ${TEST_NAME}
			@echo "\033[1;31mRemoving binary file\033[0;0m"

re:			fclean all

.PHONY:		all clean fclean re test