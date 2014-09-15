GCC = g++
HEAD = ./head
CXXFLAGS += -I$(HEAD)
EXEC = parseSkeleton
BIN = ./bin
SRC = ./src
OBJECTS = $(BIN)/main.o $(BIN)/skeleton.o $(BIN)/filehandler.o

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(GCC) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

$(BIN)/main.o: $(SRC)/main.cpp $(BIN)/skeleton.o $(BIN)/filehandler.o
	$(GCC) -c $(CXXFLAGS) $^ -o $@

$(BIN)/filehandler.o: $(SRC)/filehandler.cpp $(BIN)/skeleton.o
	$(GCC) -c $(CXXFLAGS) $^ -o $@

$(BIN)/skeleton.o: $(SRC)/skeleton.cpp
	$(GCC) -c $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BIN)/*.o
	rm -rf $(EXEC)