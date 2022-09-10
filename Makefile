main.out: Organism.o Universe.o main.o
	g++ -o main.out Organism.o Universe.o main.o

Organism.o: ./Organisms/Organism.cpp ./0_headers/Organism.h
	g++ -c -g  ./Organisms/Organism.cpp

Universe.o: ./Sources/Universe.cpp ./headers/Universe.hpp
	g++ -c -g  ./Sources/Universe.cpp

main.o: ./Sources/main.cpp
	g++ -c -g  ./Sources/main.cpp

clean: 
	rm *.i *.o *.out *.exe
