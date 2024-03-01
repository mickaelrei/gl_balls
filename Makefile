CFLAGS = -lglfw -lGL -lstdc++ -Wall

INCLUDE_GLAD = ./glad/include
INCLUDE = ./include

SOURCE = main.cpp \
		 ./glad/src/glad.c

OBJ_DIR = obj
TARGET_DIR = bin

TARGET = main

all:
	if [ ! -d $(TARGET_DIR) ]; then mkdir $(TARGET_DIR); fi
	$(CXX) -I$(INCLUDE) -I$(INCLUDE_GLAD) $(SOURCE) -o $(TARGET_DIR)/$(TARGET) $(CFLAGS)

run:
	./$(TARGET_DIR)/$(TARGET)

clean:
	rm $(TARGET_DIR)/*