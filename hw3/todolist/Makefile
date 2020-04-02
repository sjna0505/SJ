all: todolist-test

todolist-test: todolist.cpp todolist.h todolist-test.cpp
	g++ -g -std=gnu++11 -Wall todolist.cpp todolist-test.cpp -o todolist-test

clean:
	rm -f *.o todolist-test