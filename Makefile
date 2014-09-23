#Variables
GCC = g++
HEAD = ./head
CXXFLAGS += -I$(HEAD)
DEBUGFLAGS = -Wall -Wextra -ggdb3
DEBUG = 
EXEC = parseSkeleton
EXDEBUG = $(EXEC).d
BIN = ./bin
SRC = ./src
SKELETONS = $(BIN)/skeleton.o $(BIN)/rad_skeleton.o
COMPUTE = $(BIN)/radcompute.o
UTIL = $(BIN)/filehandler.o $(BIN)/histogram.o
OBJECTS = $(BIN)/main.o $(SKELETONS) $(UTIL) $(COMPUTE) 

#Compile all target
all: $(EXEC)

#Compile debug target
debug: DEBUG += $(DEBUGFLAGS)
debug: $(EXDEBUG)

$(EXDEBUG): $(OBJECTS)
	$(GCC) $(DEBUG) $(CXXFLAGS) $^ -o $@

$(EXEC): $(OBJECTS)
	$(GCC) $(DEBUG) $(CXXFLAGS) $^ -o $@

$(BIN)/main.o: $(SRC)/main.cpp $(BIN)/skeleton.o $(BIN)/filehandler.o $(BIN)/rad_skeleton.o $(BIN)/radcompute.o
	$(GCC) $(DEBUG) -c $(CXXFLAGS) $^ -o $@

$(BIN)/radcompute.o: $(SRC)/radcompute.cpp $(BIN)/rad_skeleton.o $(BIN)/histogram.o $(BIN)/filehandler.o
	$(GCC) $(DEBUG) -c $(CXXFLAGS) $^ -o $@

$(BIN)/filehandler.o: $(SRC)/filehandler.cpp $(BIN)/skeleton.o
	$(GCC) $(DEBUG) -c $(CXXFLAGS) $^ -o $@

$(BIN)/rad_skeleton.o: $(SRC)/rad_skeleton.cpp $(BIN)/skeleton.o
	$(GCC) $(DEBUG) -c $(CXXFLAGS) $^ -o $@

$(BIN)/skeleton.o: $(SRC)/skeleton.cpp
	$(GCC) $(DEBUG) -c $(CXXFLAGS) $^ -o $@

$(BIN)/histogram.o: $(SRC)/histogram.cpp
	$(GCC) $(DEBUG) -c $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BIN)/*.o
	rm -rf $(EXEC)
	rm -rf $(EXDEBUG)
