GCC = g++
HEAD = ./head
CXXFLAGS += -I$(HEAD)
EXEC = parseSkeleton
BIN = ./bin
SRC = ./src
OBJECTS = $(BIN)/main.o

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(GCC) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

$(BIN)/main.o: $(SRC)/main.cpp
	$(GCC) -c $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BIN)/*.o
	rm -rf $(EXEC)