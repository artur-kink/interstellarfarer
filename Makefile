
CC=g++
RM=rm

INCLUDES=-I/home/malo/SDL2-2.0.0/include/
LIBRARIES=-lSDL2

CLIENT_SOURCES=client/main.cpp \
    client/client.cpp

CLIENT_OBJECTS=$(CLIENT_SOURCES:.cpp=.o)

.PHONY: all client clean
all: client

client: $(CLIENT_OBJECTS)
	$(CC) -Wl,-rpath,. -o debug/client $(CLIENT_OBJECTS) $(LIBRARIES)

$(CLIENT_OBJECTS): %.o: %.cpp
	$(CC) -g -c $(INCLUDES) -MMD -MP -MF $@.d -o $@ $<

clean: 
	$(RM) -vf $(CLIENT_OBJECTS)
