project(NSS)

add_library(lib Aph rodite.cpp lexer.cpp Organism.cpp parser.cpp simulation.cpp Traits.cpp Universe.cpp)

add_executable(NSS main.cpp)

target_link_libraries(NSS PUBLIC lib)
