all: ladder
CC=$(CXX)
ladder: ladder.o matrix.o euclid.o header.h
euclid.o: header.h
matrix.o: header.h
clean: 
	-rm *.o ladder
