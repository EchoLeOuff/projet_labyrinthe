# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lm
DEBUG = -g

# Fichiers sources
SRC = src\main.c src\generation.c src\graphe.c src\resoudre.c src\affichage.c
OBJ = $(SRC:.c=.o)
EXEC = bin\labyrinthe.exe

# Dépendances des en-têtes
DEPS = include\labyrinthe.h include\affichage.h

# Règle par défaut
all: $(EXEC)

# Règle de compilation
%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) $(DEBUG) $< -o $@

# Règle de linkage
$(EXEC): $(OBJ)
	if not exist bin mkdir bin
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXEC)

# Nettoyage
clean:
	-if exist $(EXEC) del /Q $(EXEC)
	-del /Q $(OBJ) 2>NUL || true
.PHONY: all clean