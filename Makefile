CC = g++
CPPFLAGS = -g -Wall

SOURCE = main.cpp Kitchen.cpp Chef.cpp Func.cpp
OBJ = $(SOURCE:.cpp=.o)

all: main

main: $(OBJ)
	$(CC) $^ -o $@

clean:
	rm *.o	