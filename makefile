CXX=g++
CXXFLAGS=-Wall -g 
LDFLAGS=-lGL -lGLU -lglut -lSOIL

SRC=main.cpp jogo.cpp telaMenu.cpp
OBJ=$(SRC:.cpp=.o)
TARGET=lista3

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
