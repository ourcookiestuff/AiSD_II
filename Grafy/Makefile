CC = g++
CFLAGS = -std=c++11

SRCS = bfs.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = bfs

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
