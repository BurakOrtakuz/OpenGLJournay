NAME = scop

CPPFLAGS	= -Iinclude
LDFLAGS		= -lglfw -ldl -lGL
SRC 		=	src/glad.c \
				src/main.cpp

OBJ = $(SRC:.cpp=.o)
OBJ := $(OBJ:.c=.o)
CXX = g++
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(CPPFLAGS) $(LDFLAGS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

%.o: %.c
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all