TARGET = bob
CC = gcc
CXX = g++

includeFolder = "Engine/Libraries/include/"
libFolder = "Engine/Libraries/lib/"

INCLUDES = -I$(includeFolder)
LIBRARIES = -L$(libFolder) 
CFLAGS = -Wall -ggdb -O3 $(INCLUDES)
CXXFLAGS = -Wall -ggdb -O3 -std=c++11 $(INCLUDES)
LINKERS = -lGL -lglfw3 -lfreeimage -ldl -lpthread -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor
LDFLAGS = $(LIBRARIES) $(LINKERS)

cpp_files = $(wildcard Engine/*.cpp)
cpp_files += $(wildcard Engine/Maths/*.cpp)
objects = $(cpp_files:.cpp=.o) Engine/glad.o

all: $(TARGET) 

$(TARGET): $(objects) 
	$(CXX) -o $@ $^ $(LDFLAGS)

Engine/glad.o: Engine/glad.c
	$(CC) -c -o $@ $^ $(LDFLAGS)

.PHONY : clean
clean :
	-rm $(TARGET) $(objects)