GCC = g++
HEAD = ./head
CXXFLAGS += -I$(HEAD)
EXEC = parseSkeleton
BIN = ./bin
OBJECTS = $(BIN)/main.o $(BIN)/p.o

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(GCC) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

$(BIN)/main.o: main.cpp $(BIN)/other

clean:
	rm -rf $(BIN)/*.o