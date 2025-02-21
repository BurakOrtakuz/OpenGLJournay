NAME			=	scop
RELEASE_DIR		=	release
ASSET_DIR		=	assets
Shader_DIR		=	./lib/Shaders

ifeq ($(OS),Windows_NT)
	ASSIMP_PATH		=	./lib/assimp_static
	EXT 			= 	.exe
	NAME			:= 	$(NAME)$(EXT)
	RELEASE_FLAGS	= 	-O3 -DNDEBUG -s
	INCLUDEFLAGS	= 	-Ilib -Iinclude -I$(ASSIMP_PATH)\include
	LDFLAGS			= 	-lglfw3 \
						-lgdi32\
						-lopengl32\
						-lmingw32\
						-L$(ASSIMP_PATH)/assimp_windows/lib\
						-lassimp\
						-lz

	DLL_LIST		=	libstdc++-6.dll\
						libgcc_s_seh-1.dll\
						libwinpthread-1.dll\
						glfw3.dll

	DLL_FILES		=	$(foreach dll,$(DLL_LIST),$(shell where "$(dll)" 2>NUL))
else
	NAME			=	$(NAME)
	RELEASE_FLAGS	=
	INCLUDEFLAGS	=	-Ilib -Iinclude -Ilib/assimp_linux/include
	LDFLAGS			=	-lglfw -ldl -lGL -lz -Llib/assimp_linux/lib -lassimp
#	LDFLAGS			=	-lglfw -lGL -lGLEW -lm
endif

SRC				=	lib/glad/glad.c \
					lib/stb_images/stb_image.c \

SRC 			+=	src/Utils.cpp \
					src/Window.cpp \
					src/Shader.cpp \
					src/Camera.cpp \
					src/Mesh.cpp \
					src/Model.cpp \
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

print:
	@for file in $(DLL_FILES); do \
		echo $$file; \
	done
release: $(OBJ)
	@echo "🔹 Creating release directory..."
	@mkdir -p "$(RELEASE_DIR)"

	@echo "🔹 Copying game binary..."
	@$(CXX)	$(OBJ)	$(INCLUDEFLAGS)	$(LDFLAGS) $(RELEASE_FLAGS)	-o	$(RELEASE_DIR)/$(NAME)

ifeq ($(OS),Windows_NT)
	@echo "🔹 Copying required DLLs..."
	@for dll in $(DLL_LIST); do \
		DLL_PATH=$$(where $$dll 2>&1); \
		if [ -n "$$DLL_PATH" ] && [ "$$DLL_PATH" != "nul" ]; then \
			cp "$$DLL_PATH" "$(RELEASE_DIR)/"; \
		else \
			echo "⚠️ Warning: $$dll is missing!"; \
		fi; \
	done
else
	@echo "🔹 Copying required shared libraries..."
	@for lib in $(SHARED_LIBS); do \
		if [ -f "$$lib" ]; then \
			cp "$$lib" "$(RELEASE_DIR)/"; \
		else \
			echo "⚠️ Warning: $$lib is missing!"; \
		fi; \
	done
endif

	@echo "🔹 Copying assets..."
	@cp -r $(ASSET_DIR) "$(RELEASE_DIR)/" 2>/dev/null || echo "⚠️ Warning: Some assets may be missing!"

	@echo "🔹 Copying shaders..."
	@mkdir -p "$(RELEASE_DIR)/lib"
	@cp -r $(Shader_DIR) "$(RELEASE_DIR)/lib" 2>/dev/null || echo "⚠️ Warning: Some shaders may be missing!"
	@echo "✅ Release build is ready in '$(RELEASE_DIR)'!"

rc: releaseclean

releaseclean:
	@$(RM) $(RELEASE_DIR)

rr: rerelease

rerelease: rc release

.PHONY: all c clean fc fclean re run print release rc releaseclean rr rerelease