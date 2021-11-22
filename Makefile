NAME		= ft
TEST_NAME	= std
SRCS_PATH	= ./
OBJS_PATH	= ./objs/
SRCSC		= main.cpp

SRCSH		= 
SRCS		= $(addprefix $(SRCS_PATH),$(SRCSC))
OBJS 		= $(addprefix $(OBJS_PATH),$(OBJS_NAME))
OBJS_NAME	= $(SRCSC:%.cpp=%.o)
LIBS 		= 
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
CXX			= clang++

all:		${NAME}

.c.o: 		${OBJS}
			${CXX} ${CXXFLAGS} -cpp $< -o ${<:.cpp=.o}

$(NAME):	${OBJS} ${SRCSH}
			@${CXX} ${CXXFLAGS} ${OBJS} ${LIBS} -o ${NAME}
			@echo "\033[1;33m${NAME} program generated."
			@${CXX} ${CXXFLAGS} ${OBJS} ${LIBS} -o ${TEST_NAME}
			@echo "\033[1;33m${TEST_NAME} program generated."
			@echo "\n"
			@echo "\033[1;32m-------------------------------"
			@echo "\033[1;32m|    ┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐    |"
			@echo 			"|    └─┐│ ││  │  ├┤ └─┐└─┐    |"
			@echo 			"|    └─┘└─┘└─┘└─┘└─┘└─┘└─┘    |"
			@echo "\033[1;32m-------------------------------"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
				@mkdir -p $(OBJS_PATH)
				@clang++ $(CXXFLAGS) -o $@ -c $<
				@echo "\033[1;34m$@ generated."

clean:
			@rm -f ${OBJS}
			@rm -rf ./objs
			@echo "\033[1;31mRemoving .o files\033[0;0m"

fclean:		clean
			@rm -f ${NAME}
			@rm -f ${TEST_NAME}
			@echo "\033[1;31mRemoving binary file\033[0;0m"

re:			fclean all

.PHONY:		all clean fclean re