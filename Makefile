# main: Aphrodite.o Traits.o Organism.o Universe.o simulation.o main.o lexer.o parser.o
# 	g++ -o main Aphrodite.o Traits.o Organism.o Universe.o simulation.o main.o lexer.o parser.o
# Aphrodite.o: ./Sources/Aphrodite.cpp ./Headers
# 	g++ -c -g  ./Sources/Aphrodite.cpp

# Traits.o: ./Sources/Traits.cpp ./Headers
# 	g++ -c -g  ./Sources/Traits.cpp

# Organism.o: ./Sources/Organism.cpp ./Headers
# 	g++ -c -g  ./Sources/Organism.cpp

# Universe.o: ./Sources/Universe.cpp ./Headers 
# 	g++ -c -g  ./Sources/Universe.cpp

# simulation.o: ./Sources/simulation.cpp ./Headers
# 	g++ -c -g ./Sources/simulation.cpp

# lexer.o: ./Sources/lexer.cpp ./Headers
# 	g++ -c -g ./Sources/lexer.cpp

# parser.o: ./Sources/parser.cpp ./Headers
# 	g++ -c -g ./Sources/parser.cpp

# main.o: ./Sources/main.cpp
# 	g++ -c -g  ./Sources/main.cpp

# clean: 
# 	rm *.o,*.exe
