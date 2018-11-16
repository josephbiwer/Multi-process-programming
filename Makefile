#Makefile for Project 6 - CSCI311

CC=cc

SRC = src
BIN = bin

world: $(SRC)/main.c $(BIN)/app.o $(BIN)/linked_list.o
	$(CC) src/main.c $(BIN)/app.o $(BIN)/linked_list.o -o output

$(BIN)/app.o: $(SRC)/app.h $(SRC)/app.c
	$(CC) -c $(SRC)/app.c -o $@

$(BIN)/linked_list.o: $(SRC)/linked_list.h $(SRC)/linked_list.c
	$(CC) -c $(SRC)/linked_list.c -o $@