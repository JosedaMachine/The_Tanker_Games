CC = gcc
CFLAGS = -lSDL2 -lSDL2main -lSDL2_image

OUTPUT = sdl2minimal
TARGET = main
OBJS = $(TARGET).o

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) -o $(OUTPUT).out $(OBJS)

%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	-rm -f *.o $(TARGET)

#gcc main.cpp -lSDL2 -lSDL2main -lSDL2_image -o test 