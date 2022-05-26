CC = g++
CFLAGS = -lSDL2 -lSDL2main -lSDL2_image

target := factorial

OUTPUT = sdl2minimal
TARGET = main
OBJS = $(TARGET).o

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) -o $(OUTPUT).out $(OBJS) $(CFLAGS)

%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	-rm -f *.o $(OUTPUT).out