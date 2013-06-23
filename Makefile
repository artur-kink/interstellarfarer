
CC=g++
RM=rm

INCLUDES=-I/home/malo/SDL2/include/ -I/home/malo/SDL2_image/ -I/usr/local/include/SDL2/
LIBRARIES=-lSDL2 -lpthread -lSDL2_image

CORE_SOURCES=core/ship.cpp \
    core/map.cpp \
    core/inputhandler.cpp

CLIENT_SOURCES=client/main.cpp \
    client/client.cpp \
    $(CORE_SOURCES)

CLIENT_OBJECTS=$(CLIENT_SOURCES:.cpp=.o)

.PHONY: all client clean

all: client

client: $(CLIENT_OBJECTS)
	$(CC) -Wl,-rpath,. -o debug/client $(CLIENT_OBJECTS) $(LIBRARIES)

$(CLIENT_OBJECTS): %.o: %.cpp
	$(CC) -g -c $(INCLUDES) -MMD -MP -MF $@.d -o $@ $<

clean:
	$(RM) -vf $(CLIENT_OBJECTS)
