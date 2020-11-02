CC = gcc

CSRCS = homework8.c
TARGET = homework8.out
OBJECTS = $(CSRCS:.c=.o)

all:$(TARGET)

$(TARGET): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ -lpthread

.c.o:
	$(CC) -c $< -o $@