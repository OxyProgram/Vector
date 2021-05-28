output: src.o 
	g++ src.o -O2 -o output -lm -lpsapi

src.o: src.cpp header.h
	g++ -c src.cpp