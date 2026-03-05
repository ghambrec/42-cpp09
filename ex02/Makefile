# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghambrec <ghambrec@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/07 10:41:45 by ghambrec          #+#    #+#              #
#    Updated: 2026/03/05 15:39:57 by ghambrec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# compiling stuff
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
FLAG_OPTIMIZING = -O2
FLAG_DEBUG = -g -O0

# header files
INCLUDE = ./inc
CXXFLAGS += -I$(INCLUDE)

# program name
NAME = PmergeMe

# source files
VPATH =	src
SRCS =	main.cpp \
		PmergeMe.cpp

# obejct files
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: CXXFLAGS += $(FLAG_OPTIMIZING)
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

# .cpp zu .o
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CXXFLAGS += $(FLAG_DEBUG)
debug: $(NAME)

run: $(NAME)
	./$(NAME) `shuf -i 1-99 -n 22 | tr "\n" " "`
# 	./$(NAME) 11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7
	

valgrind: fclean debug
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re run debug valgrind
