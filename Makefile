piece1=pawn
piece2=knight
piece3=bishop
piece4=rook
piece5=king
piece6=queen
board=board
main=main
game=game
comp=AI
piece=piece

runchess.out: $(piece1).o $(piece2).o $(piece3).o $(piece4).o $(piece5).o $(piece6).o $(main).o $(game).o $(comp).o $(piece).o $(board.o)
	g++ $(piece1).o $(piece2).o $(piece3).o $(piece4).o $(piece5).o $(piece6).o $(main).o $(game).o $(comp).o $(piece).o $(board).o -o runchess.out
$(main).o: $(main).cpp $(game).o $(game).h
	g++ -c $(main).cpp -o main.o
$(game).o: $(board).o $(board).h
	g++ -c $(game).cpp -o $(game).o
$(board).o: $(piece1).o $(piece2).o $(piece3).o $(piece4).o $(piece5).o $(piece6).o $(piece1).h $(piece2).h $(piece3).h $(piece4).h $(piece5).h $(piece6).h
	g++ -c $(board).cpp -o $(board).o
$(comp).o: 
	g++ -c $(comp).cpp -o $(comp).o
$(piece1).o: $(piece).o $(piece).h $(piece1).h
	g++ -c $(piece1).cpp -o $(piece1).o
$(piece2).o: $(piece).o $(piece).h $(piece2).h
	g++ -c $(piece2).cpp -o $(piece2).o
$(piece3).o: $(piece).o $(piece).h $(piece3).h
	g++ -c $(piece3).cpp -o $(piece3).o
$(piece4).o: $(piece).o $(piece).h $(piece4).h
	g++ -c $(piece4).cpp -o $(piece4).o
$(piece5).o: $(piece).o $(piece).h $(piece5).h
	g++ -c $(piece5).cpp -o $(piece5).o
$(piece6).o: $(piece).o $(piece).h $(piece6).h
	g++ -c $(piece6).cpp -o $(piece6).o
$(piece).o: $(piece).h
	g++ -c $(piece).cpp -o $(piece).o
clean:
	rm $(piece).o
	rm $(piece1).o
	rm $(piece2).o
	rm $(piece3).o
	rm $(piece4).o
	rm $(piece5).o
	rm $(piece6).o
	rm $(board).o
	rm $(main).o
	rm $(gmae).o
	rm $(comp).o
	rm runchess.out
