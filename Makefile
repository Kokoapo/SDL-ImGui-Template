PROJECTNAME = Program
OUTPUT_DIR = build
INCLUDE_DIRS = -Iinclude/SDL2 -Iinclude/imgui -Iinclude/Main
LIB_DIRS = -Llib
LIBS = -lmingw32 -lSDL2main -lSDL2 -limgui
flags = -mwindows
SRC = $(wildcard src/*.cpp)


all: $(OUTPUT_DIR)/$(PROJECTNAME).exe

$(OUTPUT_DIR)/$(PROJECTNAME).exe: $(SRC) copy_dlls
	g++ $(flags) $(SRC) -o $@ $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)

copy_dlls: $(OUTPUT_DIR)
	copy dlls\*.dll $(OUTPUT_DIR)

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)

# %.o: %.cpp
# 	g++ $(flags) $(INCLUDE_DIRS) -c $< -o $@
