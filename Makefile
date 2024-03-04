CFLAGS := -lglfw -lGL -lstdc++ -Wall -fsanitize=address,undefined

INCLUDE := ./include
SRC := ./src
BIN := ./bin

TARGET = $(BIN)/main

all: $(TARGET)

$(TARGET): $(BIN)/application.o $(BIN)/circle.o $(BIN)/shader.o $(BIN)/glad.o $(BIN)/verlet_object.o $(BIN)/solver.o ./main.cpp
	$(CXX) -I. -I./glad/include/glad $(BIN)/application.o $(BIN)/circle.o $(BIN)/shader.o $(BIN)/glad.o $(BIN)/verlet_object.o $(BIN)/solver.o ./main.cpp -o $(TARGET) $(CFLAGS)

$(BIN)/application.o: $(INCLUDE)/application.hpp $(SRC)/application.cpp
	$(CXX) -I. -c $(SRC)/application.cpp -o $(BIN)/application.o $(CFLAGS)

$(BIN)/circle.o: $(INCLUDE)/circle.hpp $(SRC)/circle.cpp
	$(CXX) -I. -c $(SRC)/circle.cpp -o $(BIN)/circle.o $(CFLAGS)

$(BIN)/shader.o: $(INCLUDE)/shader.hpp $(SRC)/shader.cpp
	$(CXX) -I. -c $(SRC)/shader.cpp -o $(BIN)/shader.o $(CFLAGS)

$(BIN)/glad.o: $(INCLUDE)/glad.h $(INCLUDE)/khrplatform.h $(SRC)/glad.c
	$(CXX) -I. -c $(SRC)/glad.c -o $(BIN)/glad.o $(CFLAGS)

$(BIN)/verlet_object.o: $(SRC)/verlet_object.cpp $(INCLUDE)/verlet_object.hpp
	$(CXX) -I. -c $(SRC)/verlet_object.cpp -o $(BIN)/verlet_object.o $(CFLAGS)

$(BIN)/solver.o: $(SRC)/solver.cpp $(INCLUDE)/solver.hpp
	$(CXX) -I. -c $(SRC)/solver.cpp -o $(BIN)/solver.o $(CFLAGS)

clean:
	rm $(BIN)/*