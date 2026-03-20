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
    # Linux garde le lien statique comme prévu par tes amis
    CXXFLAGS += -DSFML_STATIC
    CPPFLAGS += -I/usr/include
    LIBS = ./lib/linux/libsfml-graphics-s.a \
           ./lib/linux/libsfml-window-s.a \
           ./lib/linux/libsfml-system-s.a \
           -lGL -lX11 -lXrandr -lXcursor -lXi -ludev -lpthread -lfreetype
endif

ifeq ($(UNAME), Darwin)
    # Mac utilise Homebrew et le lien DYNAMIQUE (plus stable sur macOS)
    BREW_PREFIX := $(shell brew --prefix)
    CPPFLAGS += -I$(BREW_PREFIX)/include
    LDFLAGS += -L$(BREW_PREFIX)/lib
    # On NE met PAS -DSFML_STATIC ici
    LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lfreetype \
           -framework OpenGL -framework Cocoa -framework IOKit \
           -framework CoreVideo -framework Carbon
endif

ifeq ($(OS), Windows_NT)
    CXXFLAGS += -DSFML_STATIC
    LIBS = ./lib/win/libsfml-graphics-s.a \
           ./lib/win/libsfml-window-s.a \
           ./lib/win/libsfml-system-s.a \
           -lopengl32 -lgdi32 -lwinmm -lfreetype
endif

# --- Cibles ---

OBJ = $(OBJ_DIR)/mainTest.o $(OBJ_DIR)/IHM.o $(OBJ_DIR)/Game.o \
      $(OBJ_DIR)/Player.o $(OBJ_DIR)/Enemy.o $(OBJ_DIR)/Shop.o $(OBJ_DIR)/Inventory.o \
      $(OBJ_DIR)/Bullet.o $(OBJ_DIR)/Position.o $(OBJ_DIR)/MainMenu.o $(OBJ_DIR)/Map.o

TARGET = $(BIN_DIR)/PiercingTime

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

# Règle générique pour éviter la répétition
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)