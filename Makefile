#Author: Tomas Jelinek (jelint11)

CFLAGS := -g -Wall -pedantic -Wno-long-long -O0 -ggdb
CC := g++
SRC := ./src/
OBJ := ./objects/
BINARY := ./jelint11

.PHONY: all
.PHONY: compile
.PHONY: run
.PHONY: clean
.PHONY: doc

all: $(OBJ)main.o $(OBJ)ChessBoard.o $(OBJ)ChessPiece.o $(OBJ)ChessInterface.o
	make compile
	make doc  
     
compile: $(BINARY)
	

run: $(BINARY)
	$(BINARY)
     
clean:
	rm -rf $(OBJ) doc $(BINARY)

doc:
	doxygen $(SRC)Doxyfile

$(BINARY): $(OBJ)main.o $(OBJ)ChessBoard.o $(OBJ)ChessPiece.o $(OBJ)ChessInterface.o
	mkdir -p objects
	$(CC) $(CFLAGS) $(OBJ)main.o $(OBJ)ChessBoard.o $(OBJ)ChessPiece.o $(OBJ)ChessInterface.o -o $(BINARY) -lncurses

$(OBJ)main.o: $(SRC)main.cpp
	mkdir -p objects
	$(CC) $(CFLAGS) -c $(SRC)main.cpp -o $(OBJ)main.o

$(OBJ)ChessBoard.o: $(SRC)ChessBoard.cpp
	mkdir -p objects
	$(CC) $(CFLAGS) -c $(SRC)ChessBoard.cpp -o $(OBJ)ChessBoard.o

$(OBJ)ChessPiece.o: $(SRC)ChessPiece.cpp
	mkdir -p objects
	$(CC) $(CFLAGS) -c $(SRC)ChessPiece.cpp -o $(OBJ)ChessPiece.o

$(OBJ)ChessInterface.o: $(SRC)ChessInterface.cpp
	mkdir -p objects
	$(CC) $(CFLAGS) -c $(SRC)ChessInterface.cpp -o $(OBJ)ChessInterface.o


	
