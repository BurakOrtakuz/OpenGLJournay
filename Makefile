NAME			=	scop

INCLUDEFLAGS	=	-Ilib -Iinclude 
LDFLAGS			=	-lglfw -ldl -lGL

SRC				=	lib/glad/glad.c \
					lib/stb_images/stb_image.c \

SRC 			+=	src/Utils.cpp \
					src/Window.cpp \
					src/Shader.cpp \
					src/Camera.cpp \
					src/main.cpp

OBJDIR			=	obj
OBJ				=	$(SRC:%.cpp=$(OBJDIR)/%.o)
OBJ				:=	$(OBJ:%.c=$(OBJDIR)/%.o)

CXX				=	c++
CC				=	gcc

RM				=	rm -rf

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX)	$(OBJ)	$(INCLUDEFLAGS)	$(LDFLAGS)	-o	$(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(INCLUDEFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(INCLUDEFLAGS) -c $< -o $@

c: clean
clean:
	@$(RM) $(OBJDIR)/*

fc: fclean
fclean: clean
	@$(RM) $(NAME)

re: fclean all

run : all
	./$(NAME)
.PHONY: all c clean fc fclean re run