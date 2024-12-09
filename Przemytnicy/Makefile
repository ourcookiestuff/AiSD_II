CC = g++
CFLAGS = -std=c++11

SRCS = prze.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = prze

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
