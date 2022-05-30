# ########################################################################
# ####################### Makefile Template ##############################
# ########################################################################

# # Compiler settings - Can be customized.
# CC = g++
# CXXFLAGS = -std=c++17 -Wall -g
# LDFLAGS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lpthread

# # Makefile settings - Can be customized.
# APPNAME = Server_TankerGames.out
# EXT = .cpp
# SRCDIR = src
# OBJDIR = obj

# ############## Do not change anything from here downwards! #############
# SRC = $(wildcard $(SRCDIR)/*$(EXT))
# OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
# DEP = $(OBJ:$(OBJDIR)/%.o=%.d)
# # UNIX-based OS variables & settings
# RM = rm
# DELOBJ = $(OBJ)
# # Windows OS variables & settings
# DEL = del
# EXE = .exe
# WDELOBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)\\%.o)

# ########################################################################
# ####################### Targets beginning here #########################
# ########################################################################

# all: $(APPNAME)

# # Builds the app
# $(APPNAME): $(OBJ)
# 	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# # Creates the dependecy rules
# %.d: $(SRCDIR)/%$(EXT)
# 	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# # Includes all .h files
# -include $(DEP)

# # Building rule for .o files and its .c/.cpp in combination with all .h
# $(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
# 	$(CC) $(CXXFLAGS) -o $@ -c $<

# ################### Cleaning rules for Unix-based OS ###################
# # Cleans complete project
# .PHONY: clean
# clean:
# 	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# # Cleans only all files with the extension .d
# .PHONY: cleandep
# cleandep:
# 	$(RM) $(DEP)

SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp) 
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(SRC_DIR)/%.o,$(SRC_FILES))
EXEC_FILE := Client_TankerGames


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