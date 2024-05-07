NAME       := ConsoleFlappy
CXX        := c++
CXXFLAGS   := -Wall -Wextra -Werror -g
LDFLAGS    := -lncurses
VPATH      := ./srcs/
SRCS       := main.cpp Game.cpp
OBJ_DIR    := ./objs
OBJS       := $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: install_deps $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

install_deps:
	@echo "Checking for ncurses..."
	@./install_ncurses.sh

.PHONY: all clean fclean re install_deps
