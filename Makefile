cc = g++
cflags = '-Wall'
ldflags = '-lboost_regex'
#include = -Iutils/
flags = -std=c++11

OBJ = todo.o

todo: $(OBJ)
	$(cc) $(cflags) -o todo $(OBJ) $(ldflags) $(flags)
	rm $(OBJ)

todo.o: todo.cpp
	$(cc) -c $(include) todo.cpp $(flags)

.PHONY : clean install

clean:
	#rm $(OBJ)

install:
	cp ./todo /usr/local/bin
