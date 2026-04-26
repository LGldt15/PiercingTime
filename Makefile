# --- OS Detection ---
ifeq ($(OS),Windows_NT)
    PLATFORM := Windows
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        PLATFORM := Linux
    endif
    ifeq ($(UNAME_S),Darwin)
        PLATFORM := Darwin
    endif
endif

#PLATFORM=Windows
# --- Global Settings ---
CXXFLAGS := -Wall -O2 -std=c++17
CPPFLAGS := 
LDFLAGS  := 
OBJ_DIR  := ./obj
BIN_DIR  := ./bin
SRC_DIR  := ./src

# --- Objects common to ALL platforms ---
# (Removed IHMServeur.o from here)
CORE_OBJ := $(OBJ_DIR)/IHM.o $(OBJ_DIR)/Game.o $(OBJ_DIR)/Player.o \
            $(OBJ_DIR)/Enemy.o $(OBJ_DIR)/Shop.o $(OBJ_DIR)/Inventory.o \
            $(OBJ_DIR)/Bullet.o $(OBJ_DIR)/Position.o $(OBJ_DIR)/MainMenu.o \
            $(OBJ_DIR)/Map.o

# --- Platform Specific Configuration ---
ifeq ($(PLATFORM), Linux)
    CXX := g++
    CXXFLAGS += -DSFML_STATIC
    CPPFLAGS += -I./include
    LIBS := ./lib/linux/libsfml-graphics-s.a \
            ./lib/linux/libsfml-window-s.a \
            ./lib/linux/libsfml-system-s.a \
            ./lib/linux/libsfml-network-s.a \
            -lGL -lX11 -lXrandr -lXcursor -lXi -ludev -lpthread -lfreetype
    
    # Linux specific objects and targets
    LINUX_ONLY_OBJ := $(OBJ_DIR)/IHMServeur.o
    TARGETS := $(BIN_DIR)/PiercingTime $(BIN_DIR)/PiercingDis
endif

ifeq ($(PLATFORM), Windows)
    CXX := x86_64-w64-mingw32-g++
    CXXFLAGS += -DSFML_STATIC
    CPPFLAGS += -I./include -I/usr/x86_64-w64-mingw32/include
    
    # Order: SFML -> Dependencies (FreeType, JPEG) -> Windows System APIs
    LIBS := ./lib/win/libsfml-graphics-s.a \
            ./lib/win/libsfml-window-s.a \
            ./lib/win/libsfml-system-s.a \
            ./lib/win/libsfml-network-s.a \
            ./lib/win/libfreetype.a \
            -lopengl32 -lgdi32 -lwinmm -lws2_32 \
            -static-libgcc -static-libstdc++ -static
            
    LINUX_ONLY_OBJ := 
    TARGETS := $(BIN_DIR)/PiercingTime
endif


ifeq ($(PLATFORM), Darwin)
    CXX := g++
    # Utilisation des chemins Homebrew pour macOS ARM64
    CPPFLAGS += -I/opt/homebrew/include
    LDFLAGS += -L/opt/homebrew/lib
    
    # AJOUTE -lsfml-network ICI
    LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lfreetype \
            -framework OpenGL -framework Cocoa -framework IOKit \
            -framework CoreVideo -framework Carbon
    
    TARGETS := $(BIN_DIR)/PiercingTime
endif

# --- Rules ---

all: $(TARGETS)

# PiercingTime: Uses core objects + the main test file
$(BIN_DIR)/PiercingTime: $(CORE_OBJ) $(OBJ_DIR)/mainTest.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# PiercingDis: Uses core objects + Linux-only objects + dispatcher main
$(BIN_DIR)/PiercingDis: $(CORE_OBJ) $(LINUX_ONLY_OBJ) $(OBJ_DIR)/mainDispatcher.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# Generic compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean