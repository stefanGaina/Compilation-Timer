#######################################################################################################
# Copyright (C) Compilation-Timer 2024                                                                #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   18.01.2024  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to generate the Compilation-Timer executable.                    #
#######################################################################################################

CFLAGS  = `pkg-config --cflags glib-2.0` -Wall -Werror
LDFLAGS = `pkg-config --libs glib-2.0`

INCLUDES = -Iinclude

SOURCES    := $(wildcard $(SRC)/*.c)
OBJECTS    := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := compilation-timer

all: | create_dirs $(EXECUTABLE)

### CREATE DIRECTORIES ###
create_dirs:
	mkdir -p $(OBJ)
	mkdir -p $(BIN)

### BINARIES ###
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
	rm -rf $(OBJ)/*
	rm -rf $(BIN)/*
