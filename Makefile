# --- Configuration de l'OS ---
UNAME := $(shell uname)
CXX := g++
CXXFLAGS := -Wall -O2 -std=c++17 

# Dossiers
SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin

# --- Détection des OS et des Flags ---
ifeq ($(UNAME), Linux)
    CXXFLAGS += -DSFML_STATIC
    CPPFLAGS += -I/usr/include
    LIBS = ./lib/linux/libsfml-graphics-s.a \
           ./lib/linux/libsfml-window-s.a \
           ./lib/linux/libsfml-system-s.a \
           ./lib/linux/libsfml-network-s.a \
           -lGL -lX11 -lXrandr -lXcursor -lXi -ludev -lpthread -lfreetype
endif

ifeq ($(UNAME), Darwin)
    BREW_PREFIX := $(shell brew --prefix)
    CPPFLAGS += -I$(BREW_PREFIX)/include
    LDFLAGS += -L$(BREW_PREFIX)/lib
    LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lfreetype \
           -framework OpenGL -framework Cocoa -framework IOKit \
           -framework CoreVideo -framework Carbon
endif

ifeq ($(OS), Windows_NT)
    CXX = x86_64-w64-mingw32-g++
    CXXFLAGS += -DSFML_STATIC
    CPPFLAGS += -I./include
    LIBS = ./lib/win/libsfml-graphics-s.a \
           ./lib/win/libsfml-window-s.a \
           ./lib/win/libsfml-system-s.a \
           ./lib/win/libsfml-network-s.a \
           -lopengl32 -lgdi32 -lwinmm -static
endif

# --- Objets ---

# Objets communs à tous les exécutables
COMMON_OBJ = $(OBJ_DIR)/IHM.o $(OBJ_DIR)/IHMServeur.o $(OBJ_DIR)/Game.o \
             $(OBJ_DIR)/Player.o $(OBJ_DIR)/Enemy.o $(OBJ_DIR)/Shop.o $(OBJ_DIR)/Inventory.o \
             $(OBJ_DIR)/Bullet.o $(OBJ_DIR)/Position.o $(OBJ_DIR)/MainMenu.o $(OBJ_DIR)/Map.o

# Cibles finales
TARGET1 = $(BIN_DIR)/PiercingTime 
TARGET2 = $(BIN_DIR)/PiercingDis 
TARGET3 = $(BIN_DIR)/PiercingServ

# --- Règles ---

all: $(TARGET1) $(TARGET2) $(TARGET3)

# Compilation de PiercingTime (utilise mainTest.cpp)
$(TARGET1): $(COMMON_OBJ) $(OBJ_DIR)/mainTest.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# Compilation de PiercingDis (utilise mainDispatcher.cpp)
$(TARGET2): $(COMMON_OBJ) $(OBJ_DIR)/mainDispatcher.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# Compilation de PiercingServ (utilise mainServer.cpp)
$(TARGET3): $(COMMON_OBJ) $(OBJ_DIR)/mainServer.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# Règle générique pour tous les fichiers .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean