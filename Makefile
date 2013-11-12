
all: invindex.o inventry.o node.o main.o
	g++ -g -ggdb -o prj1 invindex.o inventry.o node.o main.o

node.o: node.h node.cpp
	g++ -g -ggdb -c node.cpp

inventry.o: inventry.cpp inventry.h node.h
	g++ -g -ggdb -c inventry.cpp
	
invindex.o: invindex.cpp invindex.h inventry.h node.h
	g++ -g -ggdb -c invindex.cpp

main.o : main.cpp node.h invindex.h
	g++ -g -ggdb -c main.cpp


clean:
	rm *.o
