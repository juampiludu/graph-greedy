CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SOURCES = main-prueba.c tupla.c EstructuraGrafo23.c ColoreoGrafo.c ArrayUtils.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = grafo

.PHONY: all win clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
