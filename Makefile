NAME = scop

CPPFLAGS	= -Iinclude -Iresources
LDFLAGS		= -lglfw -ldl -lGL
SRC 		=	src/glad.c \
				src/Shader.cpp \
				src/stb_image.cpp \
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

c: clean
clean:
	@$(RM) $(OBJ)

fc: fclean
fclean: clean
	@$(RM) $(NAME)

re: fclean all

run : all
	./$(NAME)
.PHONY: all clean fclean re run