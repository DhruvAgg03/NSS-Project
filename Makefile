main.out: Organism.o Universe.o simulation.o main.o
	g++ -o main.out Organism.o Universe.o simulation.o main.o

Organism.o: ./Sources/Organism.cpp ./headers/Organism.h
	g++ -c -g  ./Sources/Organism.cpp

Universe.o: ./Sources/Universe.cpp ./headers/Universe.h 
	g++ -c -g  ./Sources/Universe.cpp

simulation.o: ./Sources/simulation.cpp ./headers/Universe.h
	g++ -c -g ./Sources/simulation.cpp

main.o: ./Sources/main.cpp
	g++ -c -g  ./Sources/main.cpp

clean: 
	rm *.i *.o *.out *.exe