MACHINE= $(shell uname -s)
ifeq ($(MACHINE),Darwin)
	GFLAGS= -lsdl2 -lsdl2_image
else
	GFLAGS= -lSDL2 -lSDL2_image
endif
CC=	g++
CFLAGS =	-std=c++11 -Wall -ggdb
LD=		g++
LDFLAGS=	-L. -ggdb
AR=		ar
ARFLAGS=	rcs
piece1=	pawn
piece2=	knight
piece3=	bishop
piece4=	rook
piece5=	king
piece6=	queen
board=	board
main=	main
game=	game
comp=	AI
piece=	piece
TARGETS= chess
CMD= runchess.out

all: $(TARGETS)

cmd: $(CMD)

chess: chesslib.a LTexture.o chessboard.o
	@echo "Linking $@..."
	@$(LD) $(LDFLAGS) $(GFLAGS) -o $@ $^

LTexture.o: LTexture.cpp LTexture.h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

chessboard.o: chessboard.cpp
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

chesslib.a: $(piece1).o $(piece2).o $(piece3).o $(piece4).o $(piece5).o $(piece6).o $(game).o $(piece).o $(board).o $(comp).o
	@echo "Linking $@..."
	@$(AR) $(ARFLAGS) $@ $^

runchess.out: $(piece1).o $(piece2).o $(piece3).o $(piece4).o $(piece5).o $(piece6).o $(main).o $(game).o $(piece).o $(board).o $(comp).o
	@echo "Linking $@..."
	@$(LD) $(LDFLAGS) -o $@ $^

$(main).o: $(main).cpp
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(game).o: $(game).cpp $(game).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(board).o: $(board).cpp $(board).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(comp).o: $(comp).cpp $(comp).h 
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(piece1).o: $(piece1).cpp $(piece1).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(piece2).o: $(piece2).cpp $(piece2).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(piece3).o: $(piece3).cpp $(piece3).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(piece4).o: $(piece4).cpp $(piece4).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(piece5).o: $(piece5).cpp $(piece5).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(piece6).o: $(piece6).cpp $(piece6).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

$(piece).o: $(piece).cpp $(piece).h
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "Cleaning..."
	@rm *.a
	@rm *.o
	@rm $(TARGETS)

cleancmd:
	@echo "Cleaning CMD Program..."
	@rm *.o
	@rm runchess.out
