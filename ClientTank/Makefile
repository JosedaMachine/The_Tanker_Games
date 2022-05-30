SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) 
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%.o,$(SRC_FILES))
EXEC_FILE := TankerGames_client.out


# Linux
#
LDFLAGS := -L/usr/lib/x86_64-linux-gnu -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2 -lpthread
CPPFLAGS := --std=c++17 -I/usr/include/SDL2

# OSX
#
#LDFLAGS := -F/Library/Frameworks -framework SDL2 -framework SDL2_image  -framework SDL2_ttf  -framework SDL2_mixer  -framework SDL2_net
#CPPFLAGS := -std=c++17 -I/Library/Frameworks/Headers/SDL2_image -I/Library/Frameworks/Headers -I/Library/Frameworks/Headers/SDL2_mixer -I/Library/Frameworks/Headers/SDL2_net -I/Library/Frameworks/Headers/SDL2_ttf -I/Library/Frameworks/Headers/SDL2 

$(EXEC_FILE): $(OBJ_FILES)
	g++ -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC_FILE) $(OBJ_FILES)